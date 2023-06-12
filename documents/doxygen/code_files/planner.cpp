
/**
 * @file planner.cpp
 * @authors Filippo Conti, Mattia Meneghin e Nicola Gianuzzi
 * @brief Planner module in charge of communicate with the vision package
 * @version 0.1
 * @date 2023-06-12
 * 
 * @copyright Copyright (c) 2023
 * 
 */
// Used libraries. Described in kinetics.h and movement.cpp files
#include <iostream>
#include <cmath>
#include <ctime>
#include <complex>
#include <Eigen/Dense>
#include "ros/ros.h"
#include "kinetics.h"
#include "motion/legoFound.h"
#include "motion/legoTask.h"
#include "motion/eventResult.h"

using namespace std;


#define node_name "planner_module" ///< Node name


#define sub_detect_commander "/vision/detectCommander" ///< topic where 'planner_module' is subscribed


#define pub_detect_resulter "/planner/detectResulter"  ///< topic that 'planner_module' publishes envetResult messages


#define pub_task_commander "/planner/taskCommander" ///< topic that 'planner_module' publishes commands


#define sub_task_resulter "/motion/taskResulter" ///< topic that 'planner_module' subscribes to take task from motion

/**
 * @defgroup planner_to_vision_commands
 * @brief constants used to manage commands received from vision
 * @{
 */
#define no_command 0            ///< no command
#define command_detect 1            ///< detect command
#define command_quit 2            ///< quit command
/**@}*/

/**
 * @defgroup planner_commands
 * @brief Constants used to identify commands type to send to movement
 * @{
 */
#define command_test 1          ///< test
#define command_wait 2          ///< wait
#define command_move 3          ///< move
#define command_grasp 4         ///< grasp
#define command_ungrasp 5       ///< ungrasp
#define command_def_pos 6       ///< define position
#define command_fast_catch 7    ///< fast catch
#define command_catch 8         ///< normal catch
/**@}*/

// security commands
/**
 * @defgroup planner_security_commands
 * @brief Constants used to provide security in the communication
 * @{
 */
#define command_handshake 9     ///< handshake command
#define command_auth_key 10     ///< authentication key command
/**@}*/

/**
 * @defgroup Planner_result_type
 * @brief Constants to identify the results type of an operation
 * @{
 */
#define result_error -1         ///< constant used to identify an execution error    
#define result_unknown 0        ///< constant used to identify an unknown result
#define result_completed 1      ///< constant used to identify an execution success
/**@}*/

#define queque_size 10          ///< buffer size
#define loop_wait_rate 100     ///< 10 msec of waiting
#define lego_coord_z 0.835      ///< z lego coordinate as the table height

/**
 * @brief base matrix for functions
 * 
 */
#define default_sim2bas_matrix 1.000, 0.000, 0.000, 0.500, 0.000, -1.000, 0.000, 0.350, 0.000, 0.000, -1.000, 1.750, 0.000, 0.000, 0.000, 1.000
/**
 * @brief base matrix for functions
 * 
 */
#define default_cam2sim_matrix 0.866, 0.000, 0.500, -0.400, 0.000, 1.000, 0.000, 0.530, -0.500, 0.000, 0.866, 1.400, 0.000, 0.000, 0.000, 1.000

// all relocation classes
/**
 * @defgroup Planner_relocation_classes
 * @brief  relocation classes
 * @{
 */
#define class_00_relocation 0.42, -0.000, 0.82           ///< X1-Y1-Z2              x=0.913 y=0.288 z=0.869
#define class_01_relocation 0.42, -0.111, 0.82           ///< X1-Y2-Z1
#define class_02_relocation 0.42, -0.227, 0.82           ///< X1-Y2-Z2
#define class_03_relocation 0.42, -0.355, 0.82           ///< X1-Y2-Z2-CHAMFER      x=0.913 y=0.693     //OK

#define class_04_relocation 0.3, -0.000, 0.82           ///< X1-Y2-Z2-TWINFILLET
#define class_05_relocation 0.3, -0.111, 0.82           ///< X1-Y3-Z2
#define class_06_relocation 0.3, -0.227, 0.82           ///< X1-Y3-Z2-FILLET
#define class_07_relocation 0.3, -0.355, 0.82           ///< X1-Y4-Z1

#define class_08_relocation 0.16, -0.000, 0.82           ///< X1-Y4-Z2              x=0.613 y=0.331
#define class_09_relocation 0.16, -0.227, 0.82           ///< X2-Y2-Z2
#define class_10_relocation 0.16, -0.355, 0.82           ///< X2-Y2-Z2-FILLET       x=0.616 y=0.693
/**@}*/

// custom orientation
#define class_00_orient 0.0, 0.0, 0.0   ///< orientation of lego class 0
#define class_01_orient 0.0, 0.0, 0.0   ///< orientation of lego class 1
#define class_02_orient 0.0, 0.0, 0.0   ///< orientation of lego class 2
#define class_03_orient 0.0, 0.0, 0.0   ///< orientation of lego class 3
#define class_04_orient 0.0, 0.0, 0.0   ///< orientation of lego class 4
#define class_05_orient 0.0, 0.0, 0.0   ///< orientation of lego class 5
#define class_06_orient 0.0, 0.0, 0.0   ///< orientation of lego class 6
#define class_07_orient 0.0, 0.0, 0.0   ///< orientation of lego class 7
#define class_08_orient 0.0, 0.0, 0.0   ///< orientation of lego class 8
#define class_09_orient 0.0, 0.0, 0.0   ///< orientation of lego class 9
#define class_10_orient 0.0, 0.0, 0.0   ///< orientation of lego class 10

//class real grasp diameters
#define class_00_real_grasp 60          ///< diameter of end effector to grasp lego class 0 in real world
#define class_01_real_grasp 60          ///< diameter of end effector to grasp lego class 1 in real world
#define class_02_real_grasp 60          ///< diameter of end effector to grasp lego class 2 in real world
#define class_03_real_grasp 60          ///< diameter of end effector to grasp lego class 3 in real world
#define class_04_real_grasp 60          ///< diameter of end effector to grasp lego class 4 in real world
#define class_05_real_grasp 60          ///< diameter of end effector to grasp lego class 5 in real world
#define class_06_real_grasp 60          ///< diameter of end effector to grasp lego class 6 in real world
#define class_07_real_grasp 60          ///< diameter of end effector to grasp lego class 7 in real world
#define class_08_real_grasp 60          ///< diameter of end effector to grasp lego class 8 in real world
#define class_09_real_grasp 60          ///< diameter of end effector to grasp lego class 9 in real world
#define class_10_real_grasp 60          ///< diameter of end effector to grasp lego class 10 in real world

// class real ungrasp diameters
#define class_00_real_ungrasp 100          ///< diameter of end effector to ungrasp lego class 0 in real world 
#define class_01_real_ungrasp 100          ///< diameter of end effector to ungrasp lego class 1 in real world
#define class_02_real_ungrasp 100          ///< diameter of end effector to ungrasp lego class 2 in real world
#define class_03_real_ungrasp 100          ///< diameter of end effector to ungrasp lego class 3 in real world
#define class_04_real_ungrasp 100          ///< diameter of end effector to ungrasp lego class 4 in real world
#define class_05_real_ungrasp 100          ///< diameter of end effector to ungrasp lego class 5 in real world
#define class_06_real_ungrasp 100          ///< diameter of end effector to ungrasp lego class 6 in real world
#define class_07_real_ungrasp 100          ///< diameter of end effector to ungrasp lego class 7 in real world
#define class_08_real_ungrasp 100          ///< diameter of end effector to ungrasp lego class 8 in real world
#define class_09_real_ungrasp 100          ///< diameter of end effector to ungrasp lego class 9 in real world
#define class_10_real_ungrasp 100          ///< diameter of end effector to ungrasp lego class 10 in real world

// class virtual grasp diameter
#define class_00_virt_grasp 38          ///< diameter of end effector to grasp lego class 0 in the simulation
#define class_01_virt_grasp 40          ///< diameter of end effector to grasp lego class 1 in the simulation
#define class_02_virt_grasp 40          ///< diameter of end effector to grasp lego class 2 in the simulation
#define class_03_virt_grasp 40          ///< diameter of end effector to grasp lego class 3 in the simulation
#define class_04_virt_grasp 40          ///< diameter of end effector to grasp lego class 4 in the simulation
#define class_05_virt_grasp 40          ///< diameter of end effector to grasp lego class 5 in the simulation
#define class_06_virt_grasp 40          ///< diameter of end effector to grasp lego class 6 in the simulation
#define class_07_virt_grasp 40          ///< diameter of end effector to grasp lego class 7 in the simulation
#define class_08_virt_grasp 40          ///< diameter of end effector to grasp lego class 8 in the simulation
#define class_09_virt_grasp 43          ///< diameter of end effector to grasp lego class 9 in the simulation
#define class_10_virt_grasp 43          ///< diameter of end effector to grasp lego class 10 in the simulation

// class virtual ungrasp diameter
#define class_00_virt_ungrasp 100          ///< diameter of end effector to ungrasp lego class 0 in the simulation
#define class_01_virt_ungrasp 100          ///< diameter of end effector to ungrasp lego class 1 in the simulation
#define class_02_virt_ungrasp 100          ///< diameter of end effector to ungrasp lego class 2 in the simulation
#define class_03_virt_ungrasp 100          ///< diameter of end effector to ungrasp lego class 3 in the simulation
#define class_04_virt_ungrasp 100          ///< diameter of end effector to ungrasp lego class 4 in the simulation
#define class_05_virt_ungrasp 100          ///< diameter of end effector to ungrasp lego class 5 in the simulation
#define class_06_virt_ungrasp 100          ///< diameter of end effector to ungrasp lego class 6 in the simulation
#define class_07_virt_ungrasp 100          ///< diameter of end effector to ungrasp lego class 7 in the simulation
#define class_08_virt_ungrasp 100          ///< diameter of end effector to ungrasp lego class 8 in the simulation
#define class_09_virt_ungrasp 100          ///< diameter of end effector to ungrasp lego class 9 in the simulation
#define class_10_virt_ungrasp 100          ///< diameter of end effector to ungrasp lego class 10 in the simulation

#define default_ungrasp_diam 100           ///< default value for ungrasp diameter

// commandline parameters
#define param0 "-s"                         ///< command line parameter
#define param1 "-secureOn"                  ///< command line parameter

bool verbose_flag = false;                 ///< to enable deep logging
bool verbose_security_flag = true;         ///< used to show security logs

// security section
bool security_flag = false;                ///< indicates the authentication system is active

#define key_max_resolution 1000000        ///< max key size

#define planner_secret_key   35680          ///< never transmit this key!
#define planner_preshared_key    65433          ///< used to make the first transmission
#define movement_preshared_key  92341          ///< used to read the first receive

int planner_comm_key;                               ///< used to check auth keys
int movement_comm_key;                             ///< used to create auth keys to send

int movement_auth_key;                       ///< stores the authorization key
int next_random_key;                         ///< stores the next random key

// Publishers
ros::Publisher pub_task_commander_handle;       ///< publisher
ros::Publisher pub_detect_resulter_handle;      ///< publisher

// Subscribers
ros::Subscriber sub_detect_commander_handle; ///< subscriber
ros::Subscriber sub_task_resulter_handle;      ///< subscriber

// Some control parameters
bool is_real_robot = false;             ///< false --> simulation; true --> real robot
bool keep_orientation = false;          ///< false --> load classes orientation from lego classes; true --> keep vision orientation
               
bool quit_planner = false;              ///< false --> planner active      
bool request_motion_ack = true;         ///< request an ack from movement
bool is_vision_msg_received = false;    ///< if planner receives a command from vision, this var becomes true

/**
 * @brief used to coordinate messages between planner and movement
 * @param command_id the id command to execute
 * @param start_moment  start time of the task
 * @param interval_moment       duration of the task
 */
struct WaitingTask {
        int command_id;
        ros::Time start_moment;
        ros::Duration interval_moment;
        bool busy;
};

/**
 * @brief struct used to coordinate msgs between planner and movement
 * 
 */
WaitingTask movement_task, vision_task;

// message used by vision to talk to planner
motion::legoFound msg_lego_detect;///< message used by vision to talk to planner
motion::legoTask msg_taskCommand;    ///< message used by vision to talk to planner                  
motion::eventResult msg_evento_task, msg_evento_detect;///< message used by vision to talk to planner

objectPositionOrientation lego_dest; ///< lego destination

/*---------------------------------------------function headers---------------------------------------------*/

void readParams(int argc, char **argv); ///< parameters functions
void defaultFunction(); ///< function executed if there are no parameters inserted
void secureEnable();    ///< function used to enable security
void unknownUsage();    ///< function executed in error case

bool handShake(); ///< start the handshake process
int randomNumber(int max_n); ///< to generate random numbers

void subDetectCommanderCallback(const motion::legoFound::ConstPtr &msg_detect); ///< reception and analysis of a received request.
void pubDetectResulter(int risultato); ///< publish the result
void pubTaskCommander(bool s_ack); ///< publish the task 
void subTaskResulterCallback(const motion::eventResult::ConstPtr &msg_event); ///< read ack sent by movement

Eigen::Vector3f camera2SimulationR(Eigen::Vector3f simul_lego_pos); ///< adapt camera point values in virtual world for robot
Eigen::Vector3f camera2RealR(Eigen::Vector3f camera_lego_pos); ///< adapt camera point values in real world for robot
void ungraspCommand(); ///< Enlarge robot fingers
void homingCommand(); ///< move the arm to default to avoid camera interferences

void catchCommand(Eigen::Vector3f position); ///< send the complete catch command to the moviment module

void selectClass(int lego_cl);  ///< In relation to lego received from vision, load right lego parameters
ros::Time getTimeNow(); ///< Returns the current time
ros::Duration getInterval(ros::Time start_t); ///< Returns the difference between the currentTime and the start time

int generateAuthKey(); ///<  generates an encrypted authorization key
int getNextKey(int extra_d); ///< used to obtain a random key used to generate authorization key received from movement
void showKeys(); ///< shows the movement and planner keys

/*---------------------------------------------Main zone---------------------------------------------*/

int main(int argc, char **argv) {

        cout << "----------------------------" << endl;
        cout << "Starting the planner module!" << endl;
        cout << "----------------------------" << endl;
    
        ros::init(argc, argv, node_name);
        ros::NodeHandle node_handle;
        cout << "Node: " << node_name << " initialized!" << endl;

        sub_detect_commander_handle = node_handle.subscribe(sub_detect_commander, queque_size, subDetectCommanderCallback);
        cout << "Subscriber: " << sub_detect_commander << " enabled with queque: " << queque_size << endl;

        pub_detect_resulter_handle = node_handle.advertise<motion::eventResult>(pub_detect_resulter, queque_size);
        cout << "Publisher: " << pub_detect_resulter << " enabled with queque: " << queque_size << endl;

        pub_task_commander_handle = node_handle.advertise<motion::legoTask>(pub_task_commander, queque_size); 
        cout << "Publisher: " << pub_task_commander << " enabled with queque: " << queque_size << endl;

        sub_task_resulter_handle = node_handle.subscribe(sub_task_resulter, queque_size, subTaskResulterCallback);
        cout << "Subscriber: " << sub_task_resulter << " enabled with queque: " << queque_size << endl;

        ros::Rate loop_rate(loop_wait_rate);

        srand(time(NULL)); 

        movement_task.busy = false;
        vision_task.busy = false;

        cout << "----------------------------" << endl;
        cout << "Planner module ready!" << endl;
        cout << "----------------------------" << endl << endl;

        cout << "Waiting for the moviment module..." << endl;
        while (pub_task_commander_handle.getNumSubscribers() < 1) { loop_rate.sleep(); }
        cout << "Moviment module connected!" << endl;

        readParams(argc, argv);

        ungraspCommand(); 
        while (ros::ok() && movement_task.busy) {

                if (quit_planner) { break; }

                ros::spinOnce();
        } 

        homingCommand(); 
        while (ros::ok() && movement_task.busy) {

                if (quit_planner) { break; }

                ros::spinOnce();
        } 

        while (ros::ok()) {

                if (quit_planner) { break; }
                                              
                if (is_vision_msg_received && !vision_task.busy) {    

                        is_vision_msg_received = false;

                        if (msg_lego_detect.send_ack) {

                                vision_task.command_id = msg_lego_detect.command_id;
                                vision_task.start_moment = getTimeNow();
                                vision_task.busy = true;
                        }

                        Eigen::Vector3f position2move;
                        position2move << msg_lego_detect.coord_x, msg_lego_detect.coord_y, msg_lego_detect.coord_z; 

                        if (is_real_robot) { position2move = camera2SimulationR(position2move); }
                        else { position2move = camera2SimulationR(position2move); }

                        position2move(2) = lego_coord_z;
                        catchCommand(position2move);
                }

                ros::spinOnce();
        }

        cout << endl;
        cout << "----------------------------" << endl;
        cout << "Exit process invoked, closing planner module!" << endl;
        cout << "----------------------------" << endl;
        return 0;
    
}

void readParams(int argc, char **argv) {

        string parameter;

        if (argc <= 1) { defaultFunction(); }

        else {

                for (int i = 1; i < argc; i++) {

                        parameter = argv[i];

                        if (parameter == param0 || parameter == param1) { secureEnable(); }
                        else { unknownUsage(); } 
                }
        }
}

void defaultFunction() {

        security_flag = false;
        if (verbose_flag) cout << "Default function selected: NO SECURITY" << endl;
}

void secureEnable() {

        if (verbose_flag) cout << "Security mode selected!" << endl;

        if (handShake()) {
                security_flag = true;
                if (verbose_flag) cout << " Security enabled!" << endl;   
        } else {
                security_flag = false;
                if (verbose_flag) cout << " Fail to enable security system!" << endl;
        }
}

void unknownUsage() {

        cout << "----------------------------------------------" << endl;
        cout << "Unknown or too much parameters" << endl;
        cout << "----------------------------------------------" << endl;
        cout << "USAGE: " << endl;
        cout << "-s or -secureOn to enable security system " << endl;
        cout << "----------------------------------------------" << endl;
        cout << endl;
}

bool handShake() {

        if (verbose_security_flag) cout << endl << "PLANNER HANDSHAKE!!!!" << endl;

        // generate current base key for the day
        planner_comm_key = planner_secret_key + randomNumber(key_max_resolution);
        if (verbose_security_flag) cout << "Planner communication key generated: " << planner_comm_key << endl;

        // generate the comm key to send
        msg_taskCommand.authkey = planner_comm_key + planner_preshared_key;
        if (verbose_security_flag) cout << "Planner encoded communication key to send: " << msg_taskCommand.authkey << endl;
        msg_taskCommand.command_id = command_handshake; 
        pubTaskCommander(true);

        // wait handshake answer        
        if (verbose_security_flag) cout << "Waiting for handshake answer..." << endl;

        while (ros::ok() && movement_task.busy) {

                if (quit_planner) { break; }

                ros::spinOnce();
        } 

        if (verbose_security_flag) cout << "Movement encoded communication key received: " << msg_evento_task.extra_data << endl;

        // get the other comm key
        movement_comm_key = msg_evento_task.extra_data - movement_preshared_key;
        if (verbose_security_flag) cout << "Movement communication key received: " << movement_comm_key << endl;

        // --------------------- PART 2 ------------------------------------

        // generate next random key
        next_random_key = randomNumber(key_max_resolution);
        if (verbose_security_flag) cout << "Random key generated: " << next_random_key << endl;

        // ask for auth key and send next random key
        msg_taskCommand.authkey = next_random_key + planner_comm_key;
        if (verbose_security_flag) cout << "Random encoded key to send: " << msg_taskCommand.authkey << endl;

        msg_taskCommand.command_id = command_auth_key; 
        pubTaskCommander(true);
        if (verbose_security_flag) cout << "Random encoded key sent!" << endl;

         // wait auth key answer        
        if (verbose_security_flag) cout << "Waiting for auth key answer..." << endl;

        while (ros::ok() && movement_task.busy) {

                if (quit_planner) { break; }

                ros::spinOnce();
        }        

        // read the auth key
        if (verbose_security_flag) cout << "Encoded Auth key received: " << msg_evento_task.extra_data << endl;

        // decode it
        movement_auth_key = msg_evento_task.extra_data - movement_comm_key;
        if (verbose_security_flag) cout << "Auth key received: " << movement_auth_key << endl;

        if (verbose_security_flag) cout << "SECURE MODE ON!" << endl;
        showKeys();

        return true;
}

int randomNumber(int max_n) {

        int random_n = rand() % (max_n + 1);
        return random_n;       
}

/*---------------------------------------------Implemented functions---------------------------------------------*/

void subDetectCommanderCallback(const motion::legoFound::ConstPtr &msg_detect) {

        if (vision_task.busy) {

                if (verbose_flag) cout << "Planner is busy at time..." << endl;
                return;
        }

        if (msg_detect->command_id == no_command) {

                is_vision_msg_received = false; 
                if (verbose_flag) cout << "No command!" << endl;
        
        } else if (msg_detect->command_id == command_detect) {

                quit_planner = false;

                msg_lego_detect.command_id = msg_detect->command_id;
                msg_lego_detect.send_ack = msg_detect->send_ack; 
                msg_lego_detect.lego_class = msg_detect->lego_class;
                msg_lego_detect.coord_x = msg_detect->coord_x;
                msg_lego_detect.coord_y = msg_detect->coord_y;
                msg_lego_detect.coord_z = msg_detect->coord_z;
                msg_lego_detect.rot_roll = msg_detect->rot_roll;
                msg_lego_detect.rot_pitch = msg_detect->rot_pitch;
                msg_lego_detect.rot_yaw = msg_detect->rot_yaw;

                is_vision_msg_received = true; 

                if (verbose_flag) {
                        cout << "---------------------------------------" << endl;
                        cout << "Subscriber: " << sub_detect_commander << " receved some data:" << endl;      
                        cout << "---------------------------------------" << endl;   
                        cout << "Command ID " << msg_detect->command_id << endl;
                        cout << "Send ack: " << msg_detect->send_ack << endl;
                        cout << "Lego class: " << msg_detect->lego_class << endl;
                        cout << "X coordinate: " << msg_detect->coord_x << endl;
                        cout << "Y coordinate: " << msg_detect->coord_y << endl;
                        cout << "Z coordinate: " << msg_detect->coord_z << endl;
                        cout << "Roll orientation: " << msg_detect->rot_roll << endl;
                        cout << "Pitch orientation: " << msg_detect->rot_pitch << endl;
                        cout << "Yaw orientation: " << msg_detect->rot_yaw << endl;
                        cout << "---------------------------------------" << endl;
                }
                
        } else if (msg_detect->command_id == command_quit) {

                quit_planner = true;
                if (verbose_flag) cout << "Quit request from vision!" << endl;

        } else {
              
                is_vision_msg_received = false;
                if (verbose_flag) cout << "Unsupported command!" << endl;
        }

}

void pubDetectResulter(int risultato) {

        msg_evento_detect.event_id = vision_task.command_id;
        msg_evento_detect.result_id = risultato;
        pub_detect_resulter_handle.publish(msg_evento_detect);

        if (verbose_flag) {
                cout << "---------------------------------------" << endl;
                cout << "Publisher: " << pub_detect_resulter << " sent some data:" << endl;
                cout << "---------------------------------------" << endl;
                cout << "Event ID: " << msg_evento_detect.event_id << endl;
                cout << "Result ID: " << msg_evento_detect.result_id << endl;
                cout << "---------------------------------------" << endl;
        }

        ros::Rate loop_rate(loop_wait_rate);
        loop_rate.sleep();
}

void pubTaskCommander(bool s_ack) {

        msg_taskCommand.send_ack = s_ack;

        if (security_flag) msg_taskCommand.authkey = generateAuthKey();

        pub_task_commander_handle.publish(msg_taskCommand);

        if (verbose_flag) {
                cout << "---------------------------------------" << endl;
                cout << "Publisher: " << pub_task_commander << " sent some data:" << endl;
                cout << "---------------------------------------" << endl;
                cout << "Command ID: " << msg_taskCommand.command_id << endl;
                cout << "Ack: " << msg_taskCommand.send_ack << endl;
                cout << "Wait time: " << msg_taskCommand.w_time << endl;       
                cout << "Is real robot: " << msg_taskCommand.real_robot << endl;
                cout << "X coordinate: " << msg_taskCommand.coord_x << endl;
                cout << "Y coordinate: " << msg_taskCommand.coord_y << endl;
                cout << "Z coordinate: " << msg_taskCommand.coord_z << endl;
                cout << "Roll orientation: " << msg_taskCommand.rot_roll << endl;
                cout << "Pitch orientation: " << msg_taskCommand.rot_pitch << endl;
                cout << "Yaw orientation: " << msg_taskCommand.rot_yaw << endl;
                cout << "Lego grasp diameter: " << msg_taskCommand.gasp_diam << endl;
                cout << "X destination coordinate: " << msg_taskCommand.dest_x << endl;
                cout << "Y destination coordinate: " << msg_taskCommand.dest_y << endl;
                cout << "Z destination coordinate: " << msg_taskCommand.dest_z << endl;
                cout << "Roll destination orientation: " << msg_taskCommand.dest_roll << endl;
                cout << "Pitch destination orientation: " << msg_taskCommand.dest_pitch << endl;
                cout << "Yaw destination orientation: " << msg_taskCommand.dest_yaw << endl;
                cout << "Lego ungasp diameter: " << msg_taskCommand.ungasp_diam << endl; 
                cout << "Authorization key: " << msg_taskCommand.authkey << endl; 
                cout << "---------------------------------------" << endl;
        }

        if (s_ack) {

                movement_task.command_id = msg_taskCommand.command_id;
                movement_task.start_moment = getTimeNow();
                movement_task.busy = true;

                if (verbose_flag) cout << "Processo " << movement_task.command_id << " messo in attesa" << endl;
        
        } else {

                movement_task.busy = false;                
        }        

        ros::Rate loop_rate(loop_wait_rate);
        loop_rate.sleep();
}

void subTaskResulterCallback(const motion::eventResult::ConstPtr &msg_event) {

        msg_evento_task.event_id = msg_event->event_id;
        msg_evento_task.result_id = msg_event->result_id;
        msg_evento_task.extra_data = msg_event->extra_data;

        if (verbose_flag) {
                cout << "---------------------------------------" << endl;
                cout << "Subscriber: " << sub_task_resulter << " receved some data:" << endl;
                cout << "---------------------------------------" << endl;
                cout << "Event ID: " << msg_evento_task.event_id << endl;
                cout << "Result ID: " << msg_evento_task.result_id << endl;
                cout << "Extra data: " << msg_evento_task.extra_data << endl;
                cout << "---------------------------------------" << endl;
        }

        if (movement_task.busy) {

                if (movement_task.command_id == msg_evento_task.event_id) {

                        movement_task.interval_moment = getInterval(movement_task.start_moment);
                        movement_task.busy = false;
                        if (verbose_flag) cout << "Processo " << movement_task.command_id << " completato" << endl;

                        if (security_flag) next_random_key = getNextKey(msg_evento_task.extra_data);
                }
        }

        if (vision_task.busy) {

                if (msg_evento_task.event_id == command_catch && vision_task.command_id == command_detect) {

                        pubDetectResulter(msg_evento_task.result_id);
                        vision_task.interval_moment = getInterval(vision_task.start_moment);
                        vision_task.busy = false;
                        if (verbose_flag) cout << "Task visione " << vision_task.command_id << " completato" << endl;

                        cout << endl << " Planner process ID: " << vision_task.command_id << " KPI: " << vision_task.interval_moment << " seconds!" << endl << endl;
                }
        }       
}

Eigen::Vector3f camera2SimulationR(Eigen::Vector3f simul_lego_pos) {

        Eigen::Matrix4f sim2bas_matrix;
        sim2bas_matrix << default_sim2bas_matrix;

        Eigen::Vector4f prod_vect;
        prod_vect = sim2bas_matrix.inverse() * Eigen::Vector4f(simul_lego_pos(0), simul_lego_pos(1), simul_lego_pos(2), 1);

        Eigen::Vector3f result_vect;
        result_vect << prod_vect(0), prod_vect(1), prod_vect(2);
        return result_vect;
}

Eigen::Vector3f camera2RealR(Eigen::Vector3f camera_lego_pos) {

        Eigen::Matrix4f cam2sim_matrix;
        cam2sim_matrix << default_cam2sim_matrix;

        Eigen::Vector4f prod_vect;
        prod_vect = cam2sim_matrix * Eigen::Vector4f(camera_lego_pos(0), camera_lego_pos(1), camera_lego_pos(2), 1);

        Eigen::Vector3f result_vect;
        result_vect << prod_vect(0), prod_vect(1), prod_vect(2);
        return result_vect;
}

void ungraspCommand() {

        msg_taskCommand.command_id = command_ungrasp; 
        msg_taskCommand.real_robot = is_real_robot;
        msg_taskCommand.ungasp_diam = default_ungrasp_diam;
        pubTaskCommander(request_motion_ack);
}

void homingCommand() {

        msg_taskCommand.command_id = command_def_pos; 
        msg_taskCommand.real_robot = is_real_robot;
        pubTaskCommander(request_motion_ack);
}

void catchCommand(Eigen::Vector3f position) {

        msg_taskCommand.command_id = command_catch; 
        msg_taskCommand.real_robot = is_real_robot;
        msg_taskCommand.coord_x = position(0);
        msg_taskCommand.coord_y = position(1);
        msg_taskCommand.coord_z = position(2);
        msg_taskCommand.rot_roll = msg_lego_detect.rot_roll;
        msg_taskCommand.rot_pitch = msg_lego_detect.rot_pitch;
        msg_taskCommand.rot_yaw = msg_lego_detect.rot_yaw;

        selectClass(msg_lego_detect.lego_class);
        pubTaskCommander(request_motion_ack);
}

void selectClass(int lego_cl) {

        Eigen::Vector3f position2arrive;

        switch (lego_cl) {

                case 0:         position2arrive << class_00_relocation;
                                break;

                case 1:         position2arrive << class_01_relocation;
                                break;

                case 2:         position2arrive << class_02_relocation;
                                break;

                case 3:         position2arrive << class_03_relocation;
                                break;

                case 4:         position2arrive << class_04_relocation;
                                break;

                case 5:         position2arrive << class_05_relocation;
                                break;

                case 6:         position2arrive << class_06_relocation;
                                break;

                case 7:         position2arrive << class_07_relocation;
                                break;

                case 8:         position2arrive << class_08_relocation;
                                break;

                case 9:         position2arrive << class_09_relocation;
                                break;

                case 10:        position2arrive << class_10_relocation;
                                break;

                default:        if (verbose_flag) cout << "Unsupported lego class!" << endl;
                                break;
        }

        msg_taskCommand.dest_x = position2arrive(0);
        msg_taskCommand.dest_y = position2arrive(1);
        msg_taskCommand.dest_z = position2arrive(2);

        if (keep_orientation) {

                msg_taskCommand.dest_roll = msg_taskCommand.rot_roll;
                msg_taskCommand.dest_pitch = msg_taskCommand.rot_pitch;
                msg_taskCommand.dest_yaw = msg_taskCommand.rot_yaw;

        } else {

                Eigen::Vector3f finalRotation;

                switch (lego_cl) {

                        case 0:         finalRotation << class_00_orient;
                                        break;

                        case 1:         finalRotation << class_01_orient;
                                        break;

                        case 2:         finalRotation << class_02_orient;
                                        break;

                        case 3:         finalRotation << class_03_orient;
                                        break;

                        case 4:         finalRotation << class_04_orient;
                                        break;

                        case 5:         finalRotation << class_05_orient;
                                        break;

                        case 6:         finalRotation << class_06_orient;
                                        break;

                        case 7:         finalRotation << class_07_orient;
                                        break;

                        case 8:         finalRotation << class_08_orient;
                                        break;

                        case 9:         finalRotation << class_09_orient;
                                        break;

                        case 10:        finalRotation << class_10_orient;
                                        break;

                        default:        if (verbose_flag) cout << "Unsupported lego orientation!" << endl;
                                        break;
                }

                msg_taskCommand.dest_roll = finalRotation(0);
                msg_taskCommand.dest_pitch = finalRotation(1);
                msg_taskCommand.dest_yaw = finalRotation(2);
        }

        if (is_real_robot) {

                switch (lego_cl) {

                        case 0:         msg_taskCommand.gasp_diam = class_00_real_grasp;
                                        msg_taskCommand.ungasp_diam = class_00_real_ungrasp;
                                        break;

                        case 1:         msg_taskCommand.gasp_diam = class_01_real_grasp;
                                        msg_taskCommand.ungasp_diam = class_01_real_ungrasp;
                                        break;

                        case 2:         msg_taskCommand.gasp_diam = class_02_real_grasp;
                                        msg_taskCommand.ungasp_diam = class_02_real_ungrasp;
                                        break;

                        case 3:         msg_taskCommand.gasp_diam = class_03_real_grasp;
                                        msg_taskCommand.ungasp_diam = class_03_real_ungrasp;
                                        break;

                        case 4:         msg_taskCommand.gasp_diam = class_04_real_grasp;
                                        msg_taskCommand.ungasp_diam = class_04_real_ungrasp;
                                        break;

                        case 5:         msg_taskCommand.gasp_diam = class_05_real_grasp;
                                        msg_taskCommand.ungasp_diam = class_05_real_ungrasp;
                                        break;

                        case 6:         msg_taskCommand.gasp_diam = class_06_real_grasp;
                                        msg_taskCommand.ungasp_diam = class_06_real_ungrasp;
                                        break;

                        case 7:         msg_taskCommand.gasp_diam = class_07_real_grasp;
                                        msg_taskCommand.ungasp_diam = class_07_real_ungrasp;
                                        break;

                        case 8:         msg_taskCommand.gasp_diam = class_08_real_grasp;
                                        msg_taskCommand.ungasp_diam = class_08_real_ungrasp;
                                        break;

                        case 9:         msg_taskCommand.gasp_diam = class_09_real_grasp;
                                        msg_taskCommand.ungasp_diam = class_09_real_ungrasp;
                                        break;

                        case 10:        msg_taskCommand.gasp_diam = class_10_real_grasp;
                                        msg_taskCommand.ungasp_diam = class_10_real_ungrasp;
                                        break;

                        default:        if (verbose_flag) cout << "Unsupported lego diameter!" << endl;
                                        break;
                }

        } else {

                switch (lego_cl) {

                        case 0:         msg_taskCommand.gasp_diam = class_00_virt_grasp;
                                        msg_taskCommand.ungasp_diam = class_00_virt_ungrasp;
                                        break;

                        case 1:         msg_taskCommand.gasp_diam = class_01_virt_grasp;
                                        msg_taskCommand.ungasp_diam = class_01_virt_ungrasp;
                                        break;

                        case 2:         msg_taskCommand.gasp_diam = class_02_virt_grasp;
                                        msg_taskCommand.ungasp_diam = class_02_virt_ungrasp;
                                        break;

                        case 3:         msg_taskCommand.gasp_diam = class_03_virt_grasp;
                                        msg_taskCommand.ungasp_diam = class_03_virt_ungrasp;
                                        break;

                        case 4:         msg_taskCommand.gasp_diam = class_04_virt_grasp;
                                        msg_taskCommand.ungasp_diam = class_04_virt_ungrasp;
                                        break;

                        case 5:         msg_taskCommand.gasp_diam = class_05_virt_grasp;
                                        msg_taskCommand.ungasp_diam = class_05_virt_ungrasp;
                                        break;

                        case 6:         msg_taskCommand.gasp_diam = class_06_virt_grasp;
                                        msg_taskCommand.ungasp_diam = class_06_virt_ungrasp;
                                        break;

                        case 7:         msg_taskCommand.gasp_diam = class_07_virt_grasp;
                                        msg_taskCommand.ungasp_diam = class_07_virt_ungrasp;
                                        break;

                        case 8:         msg_taskCommand.gasp_diam = class_08_virt_grasp;
                                        msg_taskCommand.ungasp_diam = class_08_virt_ungrasp;
                                        break;

                        case 9:         msg_taskCommand.gasp_diam = class_09_virt_grasp;
                                        msg_taskCommand.ungasp_diam = class_09_virt_ungrasp;
                                        break;

                        case 10:        msg_taskCommand.gasp_diam = class_10_virt_grasp;
                                        msg_taskCommand.ungasp_diam = class_10_virt_ungrasp;
                                        break;

                        default:        if (verbose_flag) cout << "Unsupported lego virtual diameter!" << endl;
                                        break;
                }
        }
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

int generateAuthKey() {

        int auth_key = movement_auth_key + next_random_key;
        if (verbose_security_flag) cout << "Generated authorization code: " << auth_key << endl;

        auth_key = auth_key + planner_comm_key;
        if (verbose_security_flag) cout << "Encoded authorization code: " << auth_key << endl;
        return auth_key;
}

int getNextKey(int extra_d) {

        if (verbose_security_flag) cout << "Next random encoded received: " << extra_d << endl;

        int next_r = extra_d - movement_comm_key;
        if (verbose_security_flag) cout << "Next random received: " << next_r << endl;

        return next_r;
}

void showKeys() {
        cout << endl;
        cout << "------------- PLANNER KEY LIST ---------------" << endl;
        cout << "Planner comm key: " << planner_comm_key << endl;
        cout << "Movement comm key: " << movement_comm_key << endl;
        cout << "Movement auth key: " << movement_auth_key << endl;
        cout << "Next random key: " << next_random_key << endl;
        cout << "--------------------------------------" << endl;
        cout << endl;
}