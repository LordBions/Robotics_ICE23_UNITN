/*
* Group: Filippo Conti, Mattia Meneghin e Nicola Gianuzzi
*
* Author: Filippo Conti
*/

#include <iostream>
#include <cmath>
#include <ctime>
#include <complex>

// Described in kinetics.h, provides a wide range of functionalities, including matrix arithmetic operations
#include <Eigen/Dense>

// Ros lib used to gain access to the ROS functionality and libraries
#include "ros/ros.h"

// Our file
#include "kinetics.h"

// *.msg files converted by catkin
#include "motion/legoTask.h"
#include "motion/eventResult.h"

// define the message type Int32. Used to work with integer values in ROS
#include <std_msgs/Int32.h>

// <std_msgs/Float64MultiArray.h> is used when working with multi-dimensional arrays of floating-point values in ROS messages
/* represents a multi-dimensional array of floating-point values. 
        It has two fields: 
                - layout, which provides metadata about the array structure, 
                - data, which is a 1-dimensional array of float64 values containing the actual data. */
#include <std_msgs/Float64MultiArray.h>

// *.msg file converted by catkin and provided by locosim
#include <ros_impedance_controller/generic_float.h>

using namespace std;

/*---------------------Some useful parameters---------------------*/ 

// Ros node name
#define node_name "moviment_module"

// topic where 'moviment_module' is subscribed
#define sub_task_commander "/planner/taskCommander"

// topic that 'moviment_module' publishes envetResult messages
#define pub_task_resulter "/motion/taskResulter"

// publisher which talks to locosim joint
#define pub_joint_commander "/ur5/joint_group_pos_controller/command"

// It is a topic where a client could command real robot gripper [Only in real robot, no simulation]
#define client_gripper_commander "/move_gripper"

// 
#define queque_size 10 // buffer size
#define loop_wait_rate 1000 // 1 msec of waiting
#define joint_number 9 // number of ur5 joints
#define position_gain 5 // parameter used to scale matrices 
#define orientation_gain 30 // parameter used to scale matrices

// constants used to identify commands
#define no_command 0
#define command_test 1
#define command_wait 2
#define command_move 3
#define command_grasp 4
#define command_ungrasp 5
#define command_def_pos 6
#define command_fast_catch 7
#define command_catch 8

// security commands
#define command_handshake 9
#define command_auth_key 10

#define result_error -1         // constant used to identify an execution error
#define result_unknown 0        // constant used to identify an unknown result
#define result_completed 1      // constant used to identify an execution success

#define z_above_object 0.7 // z default value to place the arm above an object
#define default_joint_state_vector -0.32, -0.78, -2.56, -1.63, -1.57, 3.49 // default values for the joints
#define default_target_position -0.3, -0.6, 0.4 // x, y, z   homing
#define half_point 0.0, -0.4, 0.6 // x, y, z --> used to avoid arm unknown position

// 
#define default_dt 0.001 // default time variation
#define default_max_traj_time 4 // max trajectory time: max time that robot can make a trajectory
#define sleep_time 50 // default time used to wait a command
#define damping_exponent -5 // exponent for the damping coefficient

// 
#define max_joint_speed 1.5
#define min_joint_speed -1.5
#define max_diameter_ext 130 // max fingers space  
#define min_diameter_ext 22 // min  fingers space

bool verbose_flag = false;       // to enable deep logging
bool verbose_security_flag = true;

// security section
bool security_flag = false;
bool bypass_main_ack_once = false; // usefull to change security context

#define key_max_resolution 1000000

#define movement_secret_key       73560           // never transmit this key!
#define movement_preshared_key    92341           // used to make the first transmission
#define planner_preshared_key  65433           // used to read the first receive

int movement_comm_key;                             // used to check auth keys
int planner_comm_key;                          // used to create auth keys to send

int movement_auth_key;                       // stores the authorization key
int next_random_key;                         // stores the next random key

// Declares publishers
ros::Publisher pub_joint_commander_handle, pub_task_resulter_handle;

// Declares subscriber
ros::Subscriber sub_task_commander_handle;

// Declares ServiceClient --> another way to communicate instead of topics
ros::ServiceClient client_gripper_commander_handle;


// Communication message that planner send to movement
motion::legoTask task_command;

// Ack used to response
motion::eventResult evento;

// variable to store the success of the task
int risultato_var;

// struct used to coordinate messages between planner and movement
struct ExecutingTask {
        int command_id;         // used to understand which task movement must execute
        ros::Time start_moment;
        ros::Duration interval_moment;
        bool busy;              // It shows if the movement is performing a task or not
};

ExecutingTask planner_eseguendo;
     
Eigen::VectorXf joint_state_vector(6);
Eigen::VectorXf gripper_state_vector(3);			        		

/*---------------------------------------------function headers---------------------------------------------*/


void taskCommanderCallback(const motion::legoTask::ConstPtr &msg_taskCommand); // reception and analysis of a received request. If it find an ack request in the end, it will publish eventResult message

void pubTaskResulter(int risultato); // publish the 

Eigen::Vector3f getTrajectory(double time, Eigen::Vector3f begin_position, Eigen::Vector3f final_position); // it returns the Trajectory vector using time and positions (start and end positions)

Eigen::VectorXf getJointSpeeds(Eigen::VectorXf joint_st, Eigen::Vector3f curr_position, Eigen::Vector3f destin_position, Eigen::Vector3f velocity, Eigen::Matrix3f curr_orientation, Eigen::Vector3f final_orientation); // it returns the joints speed

void updateJointStates(); // update joint state

float gripper2joints(float diameter); // returns the converted diameter of fingers

void nullCommandExecute(); // used when motion has no command to execute

void waitCommandExecute(int wait_time); // used to wait a command from planner

void moveProcedure(Eigen::Vector3f v_position, Eigen::Vector3f v_orientation, float dt); // used to move the arm

void graspObject(bool catchIt); // used to grasp objects (open-close fingers)

void moveDefaultPosition(); // move the arm to a default position

void fastCatchProcedure(); // used when the command received is command_fast_catch: goes to the object in a fast way

void catchProcedure(); // used when the command received is command_catch:  goes to the object using a full protocol

ros::Time getTimeNow(); // return the current time

ros::Duration getInterval(ros::Time start_t); // return the interval between the start time and the current time

void handShake(); // the procedure to pass the security keys

int randomNumber(int max_n); // to generate random numbers

void AuthKeySend();

bool verifyAuthKey(int auth_key);

int generateNextRandom();

void showKeys();

/*---------------------------------------------Main zone---------------------------------------------*/

int main(int argc, char **argv) {

        cout << "----------------------------" << endl;
        cout << "Starting the moviment module!" << endl;
        cout << "----------------------------" << endl;

        ros::init(argc, argv, node_name);
        ros::NodeHandle node_handle;
        cout << "Node: " << node_name << " initialized!" << endl;

        sub_task_commander_handle = node_handle.subscribe(sub_task_commander, queque_size, taskCommanderCallback);
        cout << "Subscriber: " << sub_task_commander << " enabled with queque: " << queque_size << endl;

        pub_task_resulter_handle = node_handle.advertise<motion::eventResult>(pub_task_resulter, queque_size);
        cout << "Publisher: " << pub_task_resulter << " enabled with queque: " << queque_size << endl;
   
        pub_joint_commander_handle = node_handle.advertise<std_msgs::Float64MultiArray>(pub_joint_commander, queque_size);
        cout << "Publisher: " << pub_joint_commander << " enabled with queque: " << queque_size << endl;

        client_gripper_commander_handle = node_handle.serviceClient<ros_impedance_controller::generic_float>(client_gripper_commander);
        cout << "Service client: " << client_gripper_commander << " enabled!" << endl;

        joint_state_vector << default_joint_state_vector;

        srand(time(NULL)); 

        planner_eseguendo.busy = false;

        cout << "----------------------------" << endl;
        cout << "Moviment module ready!" << endl;
        cout << "----------------------------" << endl << endl;

        while (ros::ok()) { ros::spinOnce(); }

        cout << "----------------------------" << endl;
        cout << endl << "Exit process invoked! Closing moviment module..." << endl;
        cout << "----------------------------" << endl;
        return 0;
}

/*---------------------------------------------Implemented functions---------------------------------------------*/

void taskCommanderCallback(const motion::legoTask::ConstPtr &msg_taskCommand) {

        if (planner_eseguendo.busy) {
                if (verbose_flag) cout << "Movement is busy at time..." << endl;
                return;
        }

        if (msg_taskCommand->command_id == no_command) { 
        
                if (verbose_flag) cout << endl;
                if (verbose_flag) cout << "receved a message without commands!!" << endl;
                if (verbose_flag) cout << endl;
                return;
        }

        task_command.command_id = msg_taskCommand->command_id;
        task_command.send_ack = msg_taskCommand->send_ack;
        task_command.w_time = msg_taskCommand->w_time;
        task_command.real_robot = msg_taskCommand->real_robot;
        task_command.coord_x = msg_taskCommand->coord_x;
        task_command.coord_y = msg_taskCommand->coord_y;
        task_command.coord_z = msg_taskCommand->coord_z;
        task_command.rot_roll = msg_taskCommand->rot_roll;
        task_command.rot_pitch = msg_taskCommand->rot_pitch;
        task_command.rot_yaw = msg_taskCommand->rot_yaw;
        task_command.gasp_diam = msg_taskCommand->gasp_diam;
        task_command.dest_x = msg_taskCommand->dest_x;
        task_command.dest_y = msg_taskCommand->dest_y;
        task_command.dest_z = msg_taskCommand->dest_z;
        task_command.dest_roll = msg_taskCommand->dest_roll;
        task_command.dest_pitch = msg_taskCommand->dest_pitch;
        task_command.dest_yaw = msg_taskCommand->dest_yaw;
        task_command.ungasp_diam = msg_taskCommand->ungasp_diam;
        task_command.authkey = msg_taskCommand->authkey;

        if (verbose_flag) {
                cout << "---------------------------------------" << endl;
                cout << "Subscriber: " << sub_task_commander << " receved some data:" << endl;
                cout << "---------------------------------------" << endl;
                cout << "Command id: " << msg_taskCommand->command_id << endl;
                cout << "Send ack: " << msg_taskCommand->send_ack << endl;
                cout << "Wait time: " << msg_taskCommand->w_time << endl;        
                cout << "Is real robot: " << msg_taskCommand->real_robot << endl;
                cout << "X coordinate: " << msg_taskCommand->coord_x << endl;
                cout << "Y coordinate: " << msg_taskCommand->coord_y << endl;
                cout << "Z coordinate: " << msg_taskCommand->coord_z << endl;
                cout << "Roll orientation: " << msg_taskCommand->rot_roll << endl;
                cout << "Pitch orientation: " << msg_taskCommand->rot_pitch << endl;
                cout << "Yaw orientation: " << msg_taskCommand->rot_yaw << endl; 
                cout << "Lego gasp diameter: " << msg_taskCommand->gasp_diam << endl;
                cout << "X destination coord: " << msg_taskCommand->dest_x << endl;
                cout << "Y destination coord: " << msg_taskCommand->dest_y << endl;
                cout << "Z destination coord: " << msg_taskCommand->dest_z << endl;
                cout << "Roll destination orientation: " << msg_taskCommand->dest_roll << endl;
                cout << "Pitch destination orientation: " << msg_taskCommand->dest_pitch << endl;
                cout << "Yaw destination orientation: " << msg_taskCommand->dest_yaw<< endl;
                cout << "Lego ungasp diameter: " << msg_taskCommand->ungasp_diam << endl;
                cout << "Authorization Key: " << msg_taskCommand->authkey << endl;
                cout << "---------------------------------------" << endl;
        } 

        if (task_command.send_ack) {

                planner_eseguendo.command_id = task_command.command_id;
                planner_eseguendo.start_moment = getTimeNow();
                planner_eseguendo.busy = true;

                if (security_flag) {

                if (! verifyAuthKey(msg_taskCommand->authkey)) {

                        if (verbose_security_flag) cout << endl << "INVALID AUTHORIZATION CODE!!!!" << endl << endl;
                        pubTaskResulter(result_error);
                        return;
                }
        }
        }

        Eigen::Vector3f position2move;
        Eigen::Vector3f v_orientation;
        
        switch (task_command.command_id) {

                case(command_test):     if (verbose_flag) cout << "execution of null / test command..." << endl;
                                        nullCommandExecute();
                                        if (verbose_flag) cout << "null / test command terminated" << endl;                                                                                    
                                        break;

                case(command_wait):     if (verbose_flag) cout << "execution of wait command..." << endl;
                                        waitCommandExecute(task_command.w_time);
                                        if (verbose_flag) cout << "Wait command terminated" << endl;
                                        break;

                case(command_move):     if (verbose_flag) cout << "execution of move command..." << endl;
                                        position2move << task_command.coord_x, task_command.coord_y, task_command.coord_z;
                                        v_orientation << task_command.rot_roll, task_command.rot_pitch, task_command.rot_yaw;
                                        moveProcedure(position2move, v_orientation, default_dt);
                                        if (verbose_flag) cout << "Move command terminated" << endl;
                                        break;

                case(command_grasp):    if (verbose_flag) cout << "execution of grasp command..." << endl;
                                        graspObject(true);
                                        if (verbose_flag) cout << "Grasp command terminated" << endl;
                                        break;

                case(command_ungrasp):  if (verbose_flag) cout << "execution of ungrasp command..." << endl;
                                        graspObject(false);
                                        if (verbose_flag) cout << "Ungrasp command terminated" << endl;
                                        break;             

                case(command_def_pos):  if (verbose_flag) cout << "execution of move to default position command..." << endl;
                                        moveDefaultPosition();
                                        if (verbose_flag) cout << "Move default position command terminated" << endl;
                                        break;                                                                  

                case(command_fast_catch):       if (verbose_flag) cout << "execution of fast catch command..." << endl;
                                                fastCatchProcedure();
                                                if (verbose_flag) cout << "Fast catch command terminated" << endl;
                                                break;                                                  

                case(command_catch):    if (verbose_flag) cout << "execution of catch command..." << endl;
                                        catchProcedure();
                                        if (verbose_flag) cout << "Catch command terminated" << endl;
                                        break;            

                case(command_handshake):        if (verbose_flag) cout << "execution of handshake command..." << endl;
                                                handShake();
                                                if (verbose_flag) cout << "Handshake command terminated" << endl;
                                                break;           

                case(command_auth_key):         if (verbose_flag) cout << "execution of auth key command..." << endl;
                                                AuthKeySend();
                                                if (verbose_flag) cout << "auth key command terminated" << endl;
                                                break;                                                                                                                                              

                default:                if (verbose_flag) cout << "Unsupported command receved!" << endl;
                                        break;
        }

        if (task_command.send_ack ) { pubTaskResulter(risultato_var); }
}

void pubTaskResulter(int risultato) { 
  
        evento.event_id = planner_eseguendo.command_id;
        evento.result_id = risultato;

        if (! bypass_main_ack_once) {

                if (security_flag) evento.extra_data = generateNextRandom();

                pub_task_resulter_handle.publish(evento);       

                if (verbose_flag){
                        cout << "---------------------------------------" << endl;
                        cout << "Publisher: " << pub_task_resulter << " sent some data:" << endl;
                        cout << "---------------------------------------" << endl;
                        cout << "Event ID: " << evento.event_id << endl;
                        cout << "Result ID: " << evento.result_id << endl;
                        cout << "Extra data: " << evento.extra_data << endl;
                        cout << "---------------------------------------" << endl;
                } 

        } else {

                bypass_main_ack_once = false;
                if (verbose_security_flag) cout << "Bypass main ack once!" << endl;
        }

        planner_eseguendo.interval_moment = getInterval(planner_eseguendo.start_moment);
        planner_eseguendo.busy = false;
        cout << endl << " Movement process ID: " << planner_eseguendo.command_id << " KPI: " << planner_eseguendo.interval_moment << " seconds!" << endl << endl;

        ros::Rate loop_rate(loop_wait_rate);
        loop_rate.sleep();
}

Eigen::Vector3f getTrajectory(double t_time, Eigen::Vector3f begin_position, Eigen::Vector3f final_position) {

        double time_ratio = t_time / default_max_traj_time;

        if (time_ratio > 1) { return final_position; }
        else { return final_position * time_ratio + begin_position * (1 - time_ratio); }
}

Eigen::VectorXf getJointSpeeds(Eigen::VectorXf joint_st, Eigen::Vector3f curr_position, Eigen::Vector3f destin_position, Eigen::Vector3f velocity, Eigen::Matrix3f curr_orientation, Eigen::Vector3f final_orientation) {

        Eigen::MatrixXf jacob_m;
        jacob_m = jacobMatrix(joint_st); 

        Eigen::Matrix3f final_or_rotor;
        final_or_rotor = orient2matrix(final_orientation);

        Eigen::Matrix3f pos_gain_mtx;
        pos_gain_mtx = position_gain * Eigen::Matrix3f::Identity();

        Eigen::Matrix3f or_gain_mtx;
        or_gain_mtx = orientation_gain * Eigen::Matrix3f::Identity();

        Eigen::Vector3f delta_or;
        delta_or = correctOrientation(final_or_rotor, curr_orientation);
        if (delta_or.norm() > 1) { delta_or = 0.1 * delta_or.normalized(); }

        Eigen::VectorXf velocity_gain_mtx(6);
        velocity_gain_mtx << (velocity + pos_gain_mtx * (destin_position - curr_position)), (or_gain_mtx * delta_or);

        Eigen::VectorXf joint_speeds_mtx;
        float damping_coeff = pow(10, damping_exponent);
        joint_speeds_mtx = (jacob_m + damping_coeff * Eigen::MatrixXf::Identity(6, 6)).inverse() * velocity_gain_mtx;

        for (int i = 0; i < 6; i++) {

            if (joint_speeds_mtx(i) > M_PI) { joint_speeds_mtx(i) = max_joint_speed; }
            else if (joint_speeds_mtx(i) < -M_PI) { joint_speeds_mtx(i) = min_joint_speed; }
        }

        return joint_speeds_mtx;
}

void updateJointStates() {	

        std_msgs::Float64MultiArray msg_joint_state;
        msg_joint_state.data.resize(joint_number);
    
        for (int i = 0; i < 6; i++) {
                msg_joint_state.data[i] = joint_state_vector(i);
        }

        msg_joint_state.data[6] = gripper_state_vector[0];
        msg_joint_state.data[7] = gripper_state_vector[1];
        msg_joint_state.data[8] = gripper_state_vector[2];

        pub_joint_commander_handle.publish(msg_joint_state);

        nullCommandExecute();
}

float gripper2joints(float diameter) {

        return (float) (diameter - min_diameter_ext) / (max_diameter_ext - min_diameter_ext) * (-M_PI) + M_PI;
}

void nullCommandExecute() {

        ros::Rate wait_loop(loop_wait_rate);
        wait_loop.sleep();

        risultato_var = result_completed;
}

void waitCommandExecute(int wait_time) {

        for (int i = 0; i < wait_time; i++) { nullCommandExecute(); }
        risultato_var = result_completed;
}

void moveProcedure(Eigen::Vector3f v_position, Eigen::Vector3f v_orientation, float dt) {

        end_effector start_ef, current_ef;
        start_ef = directKinematic(joint_state_vector);

        Eigen::Vector3f velocity;
        Eigen::VectorXf joint_speed_k(6);                  

        for (double i = dt; i <= default_max_traj_time; i += dt) {

            current_ef = directKinematic(joint_state_vector);

            velocity = (getTrajectory(i, start_ef.posit, v_position) - getTrajectory(i - dt, start_ef.posit, v_position)) / dt;

            joint_speed_k = getJointSpeeds(joint_state_vector, current_ef.posit, getTrajectory(i, start_ef.posit, v_position), velocity, current_ef.orient, v_orientation);

            joint_state_vector = joint_state_vector + joint_speed_k * dt;

            updateJointStates();
        }

        risultato_var = result_completed;
}

void graspObject(bool catchIt) {

        if (task_command.real_robot) {

                ros_impedance_controller::generic_float gripper_diameter;

                if (verbose_flag) cout << "Real robot grasp:" << endl;
                
                if (catchIt) {

                        if (verbose_flag) cout << "closing UR5 fingers..." << endl;
                        gripper_diameter.request.data = task_command.gasp_diam;
                        
                        nullCommandExecute();

                        client_gripper_commander_handle.call(gripper_diameter);
                        if (verbose_flag) cout << "UR5 fingers closed, possibly arround the object!" << endl;

                } else {

                        if (verbose_flag) cout << "Opening UR5 fingers..." << endl;
                        gripper_diameter.request.data = task_command.ungasp_diam;

                        nullCommandExecute();

                        client_gripper_commander_handle.call(gripper_diameter);
                        if (verbose_flag) cout << "UR5 fingers opened, possibly relased object!" << endl;
                }

                waitCommandExecute(sleep_time);

        } else {

            if (verbose_flag) cout << "Virtual robot grasp!" << endl;
            
                if (catchIt) {   

                        if (verbose_flag) cout << "closing UR5 fingers..." << endl;
                        gripper_state_vector[0] = gripper2joints(task_command.gasp_diam);
                        gripper_state_vector[1] = gripper_state_vector[0];
                        gripper_state_vector[2] = gripper_state_vector[0];

                        updateJointStates();
                        if (verbose_flag) cout << "UR5 fingers closed, possibly arround the object!" << endl;
                }

                else {

                        if (verbose_flag) cout << "Opening UR5 fingers..." << endl;
                        gripper_state_vector[0] = gripper2joints(task_command.ungasp_diam);
                        gripper_state_vector[1] = gripper_state_vector[0];
                        gripper_state_vector[2] = gripper_state_vector[0];

                        updateJointStates();
                        if (verbose_flag) cout << "UR5 fingers opened, possibly relased object!" << endl;
                }

        }

        risultato_var = result_completed;
}

void moveDefaultPosition() {

        Eigen::Vector3f default_pos_vector;
        default_pos_vector << default_target_position;

        Eigen::Vector3f v_orientation;
        v_orientation << task_command.rot_roll, task_command.rot_pitch, task_command.rot_yaw;
        moveProcedure(default_pos_vector, v_orientation, default_dt);

        risultato_var = result_completed;
}

void fastCatchProcedure() {
    
        Eigen::Vector3f position2move;
        Eigen::Vector3f v_orientation;
        if (verbose_flag) cout << "Starting fast catch procedure..." << endl;

        position2move << task_command.coord_x, task_command.coord_y, task_command.coord_z;
        v_orientation << task_command.rot_roll, task_command.rot_pitch, task_command.rot_yaw;		
        moveProcedure(position2move, v_orientation, default_dt);
        if (verbose_flag) cout << "UR5 arm is on the object" << endl;

        graspObject(true);
        if (verbose_flag) cout << "Keeping fingers closed..." << endl;
        
        position2move << task_command.dest_x, task_command.dest_y, task_command.dest_z;
        v_orientation << task_command.dest_roll, task_command.dest_pitch, task_command.dest_yaw;	       
        moveProcedure(position2move, v_orientation, default_dt);
        if (verbose_flag) cout << "UR5 arm reached the class relocation position" << endl;
                
        graspObject(false);
        if (verbose_flag) cout << "Keeping fingers open..." << endl;
        
        position2move << half_point;	  
        v_orientation << task_command.rot_roll, task_command.rot_pitch, task_command.rot_yaw;
        moveProcedure(position2move, v_orientation, default_dt);
        if (verbose_flag) cout << "UR5 arm reached the half point" << endl;   

        risultato_var = result_completed;     
}

void catchProcedure() {
    
        Eigen::Vector3f position2move;
        Eigen::Vector3f v_orientation;
        if (verbose_flag) cout << "Starting the catch procedure... going to the object" << endl;

        position2move << task_command.coord_x, task_command.coord_y, z_above_object;
        v_orientation << task_command.rot_roll, task_command.rot_pitch, task_command.rot_yaw;
        moveProcedure(position2move, v_orientation, default_dt);
        if (verbose_flag) cout << "UR5 arm is above the object ready to approach" << endl;

        position2move << task_command.coord_x, task_command.coord_y, task_command.coord_z;
        v_orientation << task_command.rot_roll, task_command.rot_pitch, task_command.rot_yaw;		
        moveProcedure(position2move, v_orientation, default_dt);
        if (verbose_flag) cout << "UR5 arm is on the object" << endl;

        graspObject(true);
        if (verbose_flag) cout << "Keeping fingers closed..." << endl;

        position2move << task_command.coord_x, task_command.coord_y, z_above_object;
        v_orientation << task_command.rot_roll, task_command.rot_pitch, task_command.rot_yaw;
        moveProcedure(position2move, v_orientation, default_dt);
        if (verbose_flag) cout << "UR5 arm is above the object ready to depart" << endl;
        
        position2move << half_point;			    
        v_orientation << task_command.rot_roll, task_command.rot_pitch, task_command.rot_yaw;
        moveProcedure(position2move, v_orientation, default_dt);         
        if (verbose_flag) cout << "UR5 arm reached the half point" << endl;

        position2move << task_command.dest_x, task_command.dest_y, z_above_object;
        v_orientation << task_command.dest_roll, task_command.dest_pitch, task_command.dest_yaw;		
        moveProcedure(position2move, v_orientation, default_dt); 
        if (verbose_flag) cout << "UR5 arm is above the class relocation, ready to pose!" << endl;
        
        position2move << task_command.dest_x, task_command.dest_y, task_command.dest_z;
        v_orientation << task_command.dest_roll, task_command.dest_pitch, task_command.dest_yaw;		
        moveProcedure(position2move, v_orientation, default_dt);
        if (verbose_flag) cout << "UR5 arm reached the class relocation position" << endl;
                
        graspObject(false);
        if (verbose_flag) cout << "Keeping fingers open..." << endl;
        
        position2move << task_command.dest_x, task_command.dest_y, z_above_object;
        v_orientation << task_command.dest_roll, task_command.dest_pitch, task_command.dest_yaw;		
        moveProcedure(position2move, v_orientation, default_dt);
        if (verbose_flag) cout << "UR5 arm is above the class relocation, ready to depart!" << endl;
        
        position2move << half_point;			    
        v_orientation << task_command.rot_roll, task_command.rot_pitch, task_command.rot_yaw;
        moveProcedure(position2move, v_orientation, default_dt);
        if (verbose_flag) cout << "UR5 arm reached the half point" << endl;

        risultato_var = result_completed;
}

ros::Time getTimeNow() {
        ros::Time start_moment = ros::Time::now();        
        if (verbose_flag) cout << "momento in secondi: " << start_moment.sec << endl;
        if (verbose_flag) cout << "momento in nano secondi: " << start_moment.nsec << endl;
        return start_moment;
}

ros::Duration getInterval(ros::Time start_t) {
        if (verbose_flag) cout << "momento finale: " << endl;
        ros::Time end_moment = getTimeNow(); 

        ros:: Duration interval_moment = end_moment - start_t;
        if (verbose_flag) cout << "momento intervallo in secondi: " << interval_moment.sec << endl;
        if (verbose_flag) cout << "momento intervallo in nano secondi: " << interval_moment.nsec << endl;
        return interval_moment;
}

void handShake() {

        if (verbose_security_flag) cout << endl << "MOVEMENT HANDSHAKE!!!" << endl;

        if (verbose_security_flag) cout << "Planner encoded communication key received: " << task_command.authkey << endl;

        // get the other base key
        planner_comm_key = task_command.authkey - planner_preshared_key;
        if (verbose_security_flag) cout << "Planner communication key received: " << planner_comm_key << endl;

        // generate current key for the day
        movement_comm_key = movement_secret_key + randomNumber(key_max_resolution);
        if (verbose_security_flag) cout << "Movement communication key generated: " << movement_comm_key << endl;

        // generate the first key send
        evento.extra_data = movement_comm_key + movement_preshared_key;
        if (verbose_security_flag) cout << "Movement encoded communication key generated: " << evento.extra_data << endl; 

        risultato_var = result_completed;
}

int randomNumber(int max_n) {

        int random_n = rand() % (max_n + 1);
        return random_n;       
}

void AuthKeySend() {

        if (verbose_security_flag) cout << endl << "MOVEMENT AUTH KEY!!! " << endl;

        // get the next random key from planner
        if (verbose_security_flag) cout << "Encoded random key received: " << task_command.authkey << endl;

        next_random_key = task_command.authkey - planner_comm_key;
        if (verbose_security_flag) cout << "Random key received: " << next_random_key << endl;

        // generate the movement auth key
        movement_auth_key = randomNumber(key_max_resolution);
        if (verbose_security_flag) cout << "Auth key generated: " << movement_auth_key << endl;

        // encode it
        evento.event_id = command_auth_key;
        evento.result_id = result_completed;
        evento.extra_data = movement_auth_key + movement_comm_key;
        if (verbose_security_flag) cout << "Encoded Auth key to send: " << evento.extra_data << endl;

        // send the auth key
        pub_task_resulter_handle.publish(evento);    
        if (verbose_security_flag) cout << "Encoded Auth key sent!" << endl;

        security_flag = true;
        if (verbose_security_flag) cout << "SECURE MODE ON!!!" << endl;

        showKeys();
        bypass_main_ack_once = true;
}

bool verifyAuthKey(int auth_key) {

        if (verbose_security_flag) cout << "Encoded Auth code received: " << auth_key << endl;

        int auth_code = auth_key - planner_comm_key;
        if (verbose_security_flag) cout << "Auth code received: " << auth_code << endl;

        int verify_code = auth_code - next_random_key;
        if (verbose_security_flag) cout << "verify code received: " << verify_code << endl;

        if (verify_code == movement_auth_key) {
                if (verbose_security_flag) cout << "AUTHORIZED !!!" << endl;
                return true;
        } else {
                if (verbose_security_flag) cout << "NOT authorized" << endl;
                return false;
        }
}

int generateNextRandom() {

        int next_r = randomNumber(key_max_resolution);
        if (verbose_security_flag) cout << "Generated next random number: " << next_r << endl;
        next_random_key = next_r;

        int encoded_next_r = next_r + movement_comm_key;
        if (verbose_security_flag) cout << "Encoded next random number: " << encoded_next_r << endl;

        return encoded_next_r;
}

void showKeys() {
        cout << endl;
        cout << "------------- MOVEMENT KEY LIST ---------------" << endl;
        cout << "Planner comm key: " << planner_comm_key << endl;
        cout << "Movement comm key: " << movement_comm_key << endl;
        cout << "Movement auth key: " << movement_auth_key << endl;
        cout << "Next random key: " << next_random_key << endl;
        cout << "--------------------------------------" << endl;
        cout << endl;
}