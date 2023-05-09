/*
* Authors: Filippo Conti, Mattia Meneghin e Nicola Gianuzzi
*/

#include <iostream>
#include <cmath>
#include <complex>
#include <Eigen/Dense>
#include "ros/ros.h"
#include "kinetics.h"
#include "motion/legoTask.h"
#include <std_msgs/Int32.h>
#include <std_msgs/Float64MultiArray.h>
#include <ros_impedance_controller/generic_float.h>

using namespace std;

#define node_name "ur5_arm_publisher"
#define pub_joint_address "/ur5/joint_group_pos_controller/command"
#define pub_motion_ack_address "/motion/readyACK"
#define sub_position_address "/motion/taskCommander"
#define client_gripper_address "/move_gripper"

#define queque_size 10
#define loop_wait_rate 1000 // 1 Hz
#define joint_number 9
#define position_gain 5
#define orientation_gain 30

#define command_catch 1
#define command_move 2
#define command_grasp 3
#define command_ungrasp 4

#define default_joint_state_vector -0.32, -0.78, -2.56, -1.63, -1.57, 3.49
#define default_target_position -0.3, -0.6, 0.4 // x, y, z
#define half_point 0.0, -0.4, 0.6 // x, y, z
#define z_above_object 0.7 // z
#define null_vector 0, 0, 0

#define default_dt 0.001
#define default_max_traj_time 7
#define sleep_time 50
#define damping_exponent -5

#define virtual_graspOff_diameter 100
#define real_robot_graspOff_diameter 100
#define max_joint_speed 1.5
#define min_joint_speed -1.5
#define max_diameter_ext 130
#define min_diameter_ext 22

ros::Publisher pub_joint_handle, pub_motionReady_handle;
ros::Subscriber sub_position_handle;
ros::ServiceClient client_gripper_handle;
				    
bool is_real_robot = false;	
int command_id;		
float lego_grasp_diameter;

objectPositionOrientation obj_po_begin; 	
objectPositionOrientation obj_po_dest; 
					                      
Eigen::VectorXf joint_state_vector(6);	
Eigen::VectorXf gripper_state_vector(3);			        				                
double max_trajectory_time = default_max_traj_time;		     

void moveDefaultPosition();
void moveProcedure(Eigen::Vector3f v_position, Eigen::Vector3f v_orientation, float dt);
Eigen::Vector3f getTrajectory(double time, Eigen::Vector3f begin_position, Eigen::Vector3f final_position);
Eigen::VectorXf getJointSpeeds(Eigen::VectorXf joint_st, Eigen::Vector3f curr_position, Eigen::Vector3f destin_position, Eigen::Vector3f velocity, Eigen::Matrix3f curr_orientation, Eigen::Vector3f final_orientation);
Eigen::Vector3f correctOrientation(Eigen::Matrix3f curr_orientation, Eigen::Matrix3f final_orientation );
void updateJointStates(Eigen::VectorXf joint_st);
float gripper2joints(float diameter);
void subscriberCallback(const motion::legoTask::ConstPtr &mex);
void catchProcedure();
void graspObject(bool catchIt);
void pubReadyACK();

int main(int argc, char **argv) {

        cout << "Starting the moviment module!" << endl;
        cout << "----------------------------" << endl << endl;

        ros::init(argc, argv, node_name);
        ros::NodeHandle node_handle;
        cout << "Node: " << node_name << " initialized!" << endl;
   
        pub_joint_handle = node_handle.advertise<std_msgs::Float64MultiArray>(pub_joint_address, queque_size);
        cout << "Publisher: " << pub_joint_address << " enabled with queque: " << queque_size << endl;
    
        pub_motionReady_handle = node_handle.advertise<std_msgs::Int32>(pub_motion_ack_address, queque_size);
        cout << "Publisher: " << pub_motion_ack_address << " enabled with queque: " << queque_size << endl;

        sub_position_handle = node_handle.subscribe(sub_position_address, queque_size, subscriberCallback);
        cout << "Subscriber: " << sub_position_address << " enabled with queque: " << queque_size << endl;

        client_gripper_handle = node_handle.serviceClient<ros_impedance_controller::generic_float>(client_gripper_address);
        cout << "Service client: " << client_gripper_address << " enabled!" << endl;
        cout << "----------------------------" << endl << endl;

        joint_state_vector << default_joint_state_vector;

        graspObject(false);
        moveDefaultPosition();

        cout << "Moviment module ready!" << endl;
        while (ros::ok()) { ros::spinOnce(); }

        cout << endl << "Exit process invoked!" << endl;
        return 0;
}

void moveDefaultPosition() {

        cout << "Moving the UR5 arm to default position..." << endl;

        Eigen::Vector3f default_pos_vector;
        default_pos_vector << default_target_position;
        moveProcedure(default_pos_vector, obj_po_begin.orientation, default_dt);

        cout << "UR5 reached the default position!" << endl;
}

void moveProcedure(Eigen::Vector3f v_position, Eigen::Vector3f v_orientation, float dt) {

        end_effector start_ef, current_ef;
        start_ef = directKinematic(joint_state_vector);

        Eigen::VectorXf joint_st = joint_state_vector; 

        Eigen::Vector3f velocity;
        Eigen::VectorXf joint_speed_k(6);                  

        for (double i = dt; i <= max_trajectory_time; i += dt) {

            current_ef = directKinematic(joint_st);

            velocity = (getTrajectory(i, start_ef.posit, v_position) - getTrajectory(i - dt, start_ef.posit, v_position)) / dt;

            joint_speed_k = getJointSpeeds(joint_st, current_ef.posit, getTrajectory(i, start_ef.posit, v_position), velocity, current_ef.orient, v_orientation);

            joint_st = joint_st + joint_speed_k * dt;

            updateJointStates(joint_st);
        }

        joint_state_vector = joint_st;
}

Eigen::Vector3f getTrajectory(double time, Eigen::Vector3f begin_position, Eigen::Vector3f final_position) {

        double time_ratio = time / max_trajectory_time;

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

Eigen::Vector3f correctOrientation(Eigen::Matrix3f curr_orientation, Eigen::Matrix3f final_orientation) {
    
        Eigen::Matrix3f relative_or_mtx;
        relative_or_mtx = final_orientation.transpose() * curr_orientation;

        Eigen::MatrixXf aux_mtx(3, 2);
        aux_mtx << relative_or_mtx(2, 1), -relative_or_mtx(1, 2), relative_or_mtx(0, 2), -relative_or_mtx(2, 0), relative_or_mtx(1, 0), -relative_or_mtx(0, 1);
    
        float delta_angle_sin = (pow(aux_mtx(0, 0), 2) + pow(aux_mtx(0, 1), 2) + pow(aux_mtx(1, 0), 2) + pow(aux_mtx(1, 1), 2) + pow(aux_mtx(2, 0), 2) + pow(aux_mtx(2, 1), 2)) * 0.5;
        float delta_angle_cos = (relative_or_mtx(0, 0) + relative_or_mtx(1, 1) + relative_or_mtx(2, 2) - 1) / 2;
        float tan_angle = atan2(delta_angle_sin, delta_angle_cos);
    
        Eigen::Vector3f axis_v;
        Eigen::Vector3f or_error;
    
        if (tan_angle == 0) { or_error << null_vector; }

        else {
                axis_v = 1 / (2 * delta_angle_sin) * Eigen::Vector3f(relative_or_mtx(2, 1) - relative_or_mtx(1, 2), relative_or_mtx(0, 2) - relative_or_mtx(2, 0), relative_or_mtx(1, 0) - relative_or_mtx(0, 1));
                or_error = final_orientation * tan_angle * axis_v;
        }

        return or_error;
}

void updateJointStates(Eigen::VectorXf joint_st) {	

        std_msgs::Float64MultiArray jointState_msg_robot;
        jointState_msg_robot.data.resize(joint_number);
    
        for (int i = 0; i < 6; i++) {
                jointState_msg_robot.data[i] = joint_st(i);
        }

        jointState_msg_robot.data[6] = gripper_state_vector[0];
        jointState_msg_robot.data[7] = gripper_state_vector[1];
        jointState_msg_robot.data[8] = gripper_state_vector[2];

        pub_joint_handle.publish(jointState_msg_robot);

        ros::Rate wait_loop(loop_wait_rate);
        wait_loop.sleep();
}

float gripper2joints(float diameter) {

        return (float) (diameter - min_diameter_ext) / (max_diameter_ext - min_diameter_ext) * (-M_PI) + M_PI;
}

void subscriberCallback(const motion::legoTask::ConstPtr &mex) {

        command_id = mex->command_id;
        obj_po_begin.position(0) = mex->coord_x;
        obj_po_begin.position(1) = mex->coord_y;
        obj_po_begin.position(2) = mex->coord_z;
        obj_po_begin.orientation(0) = mex->rot_roll;
        obj_po_begin.orientation(1) = mex->rot_pitch;
        obj_po_begin.orientation(2) = mex->rot_yaw;
        lego_grasp_diameter = mex->gasp_diam;
        obj_po_dest.position(0) = mex->dest_x;
        obj_po_dest.position(1) = mex->dest_y;
        obj_po_dest.position(2) = mex->dest_z;
        obj_po_dest.orientation(0) = mex->dest_roll;
        obj_po_dest.orientation(1) = mex->dest_pitch;
        obj_po_dest.orientation(2) = mex->dest_yaw;

        cout << endl;
        cout << "Subscriber: " << sub_position_address << " receved some data:" << endl;
        cout << "Command id: " << command_id << endl;
        cout << "X coordinate: " << obj_po_begin.position(0) << endl;
        cout << "Y coordinate: " << obj_po_begin.position(1) << endl;
        cout << "Z coordinate: " << obj_po_begin.position(2) << endl;
        cout << "Roll orientation: " << obj_po_begin.orientation(0) << endl;
        cout << "Pitch orientation: " << obj_po_begin.orientation(1) << endl;
        cout << "Yaw orientation: " << obj_po_begin.orientation(2) << endl; 
        cout << "Lego diameter: " << lego_grasp_diameter << endl;
        cout << "X destination coord: " << obj_po_dest.position(0) << endl;
        cout << "Y destination coord: " << obj_po_dest.position(1) << endl;
        cout << "Z destination coord: " << obj_po_dest.position(2) << endl;
        cout << "Roll destination orientation: " << obj_po_dest.orientation(0) << endl;
        cout << "Pitch destination orientation: " << obj_po_dest.orientation(1) << endl;
        cout << "Yaw destination orientation: " << obj_po_dest.orientation(2) << endl << endl; 

        Eigen::Vector3f position2move;
        
        switch (command_id) {

                case(command_catch):    catchProcedure();  
                                        break;

                case(command_move):     position2move << obj_po_begin.position(0), obj_po_begin.position(1), obj_po_begin.position(2);
                                        moveProcedure(position2move, obj_po_begin.orientation, default_dt);
                                        break;

                case(command_grasp):    graspObject(true);
                                        break;

                case(command_ungrasp):  graspObject(false);                   

                default:                break;
        }
        
}

void catchProcedure() {
    
        Eigen::Vector3f position2move;
        cout << "Starting the catch procedure... going to the object" << endl;

        position2move << obj_po_begin.position(0), obj_po_begin.position(1), z_above_object;
        moveProcedure(position2move, obj_po_begin.orientation, default_dt);
        cout << "UR5 arm is above the object ready to approach" << endl;

        position2move << obj_po_begin.position(0), obj_po_begin.position(1), obj_po_begin.position(2);		
        moveProcedure(position2move, obj_po_begin.orientation, default_dt);
        cout << "UR5 arm is on the object" << endl;

        graspObject(true);
        cout << "Keeping fingers closed..." << endl;

        position2move << obj_po_begin.position(0), obj_po_begin.position(1), z_above_object;
        moveProcedure(position2move, obj_po_begin.orientation, default_dt);
        cout << "UR5 arm is above the object ready to depart" << endl;
        
        position2move << half_point;			    
        moveProcedure(position2move, obj_po_begin.orientation, default_dt);           
        cout << "UR5 arm reached the half point" << endl;

        position2move << obj_po_dest.position(0), obj_po_dest.position(1), z_above_object;		
        moveProcedure(position2move, obj_po_dest.orientation, default_dt);
        cout << "UR5 arm is above the class relocation, ready to pose!" << endl;
        
        position2move << obj_po_dest.position(0), obj_po_dest.position(1), obj_po_dest.position(2);	       
        moveProcedure(position2move, obj_po_dest.orientation, default_dt);
        cout << "UR5 arm reached the class relocation position" << endl;
                
        graspObject(false);
        cout << "Keeping fingers open..." << endl;
        
        position2move << obj_po_dest.position(0), obj_po_dest.position(1), z_above_object;		
        moveProcedure(position2move, obj_po_dest.orientation, default_dt);
        cout << "UR5 arm is above the class relocation, ready to depart!" << endl;
        
        position2move << half_point;	  
        moveProcedure(position2move, obj_po_dest.orientation, default_dt);
        cout << "UR5 arm reached the half point" << endl;
        
        pubReadyACK();
        cout << "Catch procedure terminated" << endl << endl;
}

void graspObject(bool catchIt) {

        ros_impedance_controller::generic_float gripper_diameter;	

        if (is_real_robot) {

                cout << "Real robot grasp:" << endl;
                
                if (catchIt) {

                        cout << "closing UR5 fingers..." << endl;
                        gripper_diameter.request.data = lego_grasp_diameter;
                        client_gripper_handle.call(gripper_diameter);
                        cout << "UR5 fingers closed, possibly arround the object!" << endl;

                } else {

                        cout << "Opening UR5 fingers..." << endl;
                        gripper_diameter.request.data = real_robot_graspOff_diameter;
                        client_gripper_handle.call(gripper_diameter);
                        cout << "UR5 fingers opened, possibly relased object!" << endl;
                }

        } else {

            cout << "Virtual robot grasp!" << endl;
            
            if (catchIt) {   

                    cout << "closing UR5 fingers..." << endl;
                    gripper_state_vector[0] = gripper2joints(lego_grasp_diameter);
                    gripper_state_vector[1] = gripper2joints(lego_grasp_diameter);
                    gripper_state_vector[2] = gripper2joints(lego_grasp_diameter);

                    updateJointStates(joint_state_vector);
                    cout << "UR5 fingers closed, possibly arround the object!" << endl;
            }

            else {

                    cout << "Opening UR5 fingers..." << endl;
                    gripper_state_vector[0] = gripper2joints(virtual_graspOff_diameter);
                    gripper_state_vector[1] = gripper2joints(virtual_graspOff_diameter);
                    gripper_state_vector[2] = gripper2joints(virtual_graspOff_diameter);

                    updateJointStates(joint_state_vector);
                    cout << "UR5 fingers opened, possibly relased object!" << endl;
            }
        }

        ros::Rate wait_loop(loop_wait_rate);
        for (int i = 0; i < sleep_time; i++) { 
                wait_loop.sleep();
        }
}

void pubReadyACK() { 

        std_msgs::Int32 ack_msg;
        ack_msg.data = 1;
        
        ros::Rate wait_loop(loop_wait_rate);   
        for (int i = 0; i < sleep_time; i++) { 
                wait_loop.sleep();
        }
        
        pub_motionReady_handle.publish(ack_msg);

        cout << endl;
        cout << "Publisher: " << pub_joint_address << " sent some data:" << endl;
        cout << "Acknowledgment: " << ack_msg << endl; 
        cout << endl;
}