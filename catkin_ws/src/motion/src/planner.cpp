/*
* Authors: Filippo Conti, Mattia Meneghin e Nicola Gianuzzi
*/

// Used libraries. Described in kinetics.h and movement.cpp files
#include <iostream>
#include <cmath>
#include <complex>
#include <Eigen/Dense>
#include "ros/ros.h"
#include "kinetics.h"
#include "motion/legoFound.h"
#include "motion/legoTask.h"
#include "motion/eventResult.h"

using namespace std;

// Node name
#define node_name "planner_module" 

// topic where 'planner_module' is subscribed
#define sub_detect_commander "/vision/detectCommander" 

// topic that 'planner_module' publishes envetResult messages
#define pub_detect_resulter "/planner/detectResulter"  

// topic that 'planner_module' publishes commands
#define pub_task_commander "/planner/taskCommander"

// topic that 'planner_module' subscribes to take task from motion
#define sub_task_resulter "/motion/taskResulter"                

// constants used to manage commands received from vision
#define no_command 0
#define command_detect 1
#define command_quit 2

// Constants used to identify commands type to send to movement
#define command_test 1
#define command_wait 2
#define command_move 3
#define command_grasp 4
#define command_ungrasp 5
#define command_def_pos 6
#define command_fast_catch 7
#define command_catch 8
#define command_handshake 9

// Constants to identify the results type
#define result_error -1         // constant used to identify an execution error    
#define result_unknown 0        // constant used to identify an unknown result
#define result_completed 1      // constant used to identify an execution success

#define queque_size 10          // buffer size
#define loop_wait_rate 100     // 10 msec of waiting
#define lego_coord_z 0.835      // z lego coordinate as the table height

#define planner_security_key 35687543210

// base matrix for functions
#define default_sim2bas_matrix 1.000, 0.000, 0.000, 0.500, 0.000, -1.000, 0.000, 0.350, 0.000, 0.000, -1.000, 1.750, 0.000, 0.000, 0.000, 1.000
#define default_cam2sim_matrix 0.866, 0.000, 0.500, -0.400, 0.000, 1.000, 0.000, 0.530, -0.500, 0.000, 0.866, 1.400, 0.000, 0.000, 0.000, 1.000

// all classes relocation
#define class_00_relocation 0.4, -0.000, 0.82           //X1-Y1-Z2
#define class_01_relocation 0.4, -0.046, 0.82           //X1-Y2-Z1
#define class_02_relocation 0.4, -0.092, 0.82           //X1-Y2-Z2
#define class_03_relocation 0.4, -0.138, 0.82           //X1-Y2-Z2-CHAMFER

#define class_04_relocation 0.3, -0.000, 0.82           //X1-Y2-Z2-TWINFILLET
#define class_05_relocation 0.3, -0.046, 0.82           //X1-Y3-Z2
#define class_06_relocation 0.3, -0.092, 0.82           //X1-Y3-Z2-FILLET
#define class_07_relocation 0.3, -0.138, 0.82           //X1-Y4-Z1

#define class_08_relocation 0.2, -0.000, 0.82           //X1-Y4-Z2
#define class_09_relocation 0.2, -0.046, 0.82           //X2-Y2-Z2
#define class_10_relocation 0.2, -0.092, 0.82           //X2-Y2-Z2-FILLET

// custom orientation
#define class_00_orient 0.0, 0.0, 0.0
#define class_01_orient 0.0, 0.0, 0.0
#define class_02_orient 0.0, 0.0, 0.0
#define class_03_orient 0.0, 0.0, 0.0
#define class_04_orient 0.0, 0.0, 0.0
#define class_05_orient 0.0, 0.0, 0.0
#define class_06_orient 0.0, 0.0, 0.0
#define class_07_orient 0.0, 0.0, 0.0
#define class_08_orient 0.0, 0.0, 0.0
#define class_09_orient 0.0, 0.0, 0.0
#define class_10_orient 0.0, 0.0, 0.0

//class real grasp diameters
#define class_00_real_grasp 60
#define class_01_real_grasp 60
#define class_02_real_grasp 60
#define class_03_real_grasp 60
#define class_04_real_grasp 60
#define class_05_real_grasp 60
#define class_06_real_grasp 60
#define class_07_real_grasp 60
#define class_08_real_grasp 60
#define class_09_real_grasp 60
#define class_10_real_grasp 60

// class real ungrasp diameters
#define class_00_real_ungrasp 100
#define class_01_real_ungrasp 100
#define class_02_real_ungrasp 100
#define class_03_real_ungrasp 100
#define class_04_real_ungrasp 100
#define class_05_real_ungrasp 100
#define class_06_real_ungrasp 100
#define class_07_real_ungrasp 100
#define class_08_real_ungrasp 100
#define class_09_real_ungrasp 100
#define class_10_real_ungrasp 100

// class virtual grasp diameter
#define class_00_virt_grasp 45
#define class_01_virt_grasp 45
#define class_02_virt_grasp 45
#define class_03_virt_grasp 45
#define class_04_virt_grasp 45
#define class_05_virt_grasp 45
#define class_06_virt_grasp 45
#define class_07_virt_grasp 45
#define class_08_virt_grasp 45
#define class_09_virt_grasp 45
#define class_10_virt_grasp 45

// class virtual ungrasp diameter
#define class_00_virt_ungrasp 100
#define class_01_virt_ungrasp 100
#define class_02_virt_ungrasp 100
#define class_03_virt_ungrasp 100
#define class_04_virt_ungrasp 100
#define class_05_virt_ungrasp 100
#define class_06_virt_ungrasp 100
#define class_07_virt_ungrasp 100
#define class_08_virt_ungrasp 100
#define class_09_virt_ungrasp 100
#define class_10_virt_ungrasp 100

// default value for ungrasp diameter
#define default_ungrasp_diam 100

// commandline parameters
#define param0 "-s"
#define param1 "-secureOn"

bool verbose_flag = false;
bool security_flag;

int encode_key;
int decode_key;

// Publishers
ros::Publisher pub_task_commander_handle, pub_detect_resulter_handle; 

// Subscribers
ros::Subscriber sub_detect_commander_handle, sub_task_resulter_handle;      

// Some control parameters
bool is_real_robot = false;             // false --> simulation; true --> real robot
bool keep_orientation = false;          // false --> load classes orientation from lego classes; true --> keep vision orientation
               
bool quit_planner = false;              // false --> planner active      
bool request_motion_ack = true;         // request an ack from movement
bool is_vision_msg_received = false;    // if planner receives a command from vision, this var becomes true

double un_momento;                      // time

// struct used to coordinate messages between planner and movement
struct WaitingTask {
        int command_id;
        double process_time;
        bool busy;
};

WaitingTask movement_task, vision_task;

// message used by vision to talk to planner
motion::legoFound msg_lego_detect;
motion::legoTask msg_taskCommand;                        
motion::eventResult msg_evento_task, msg_evento_detect;

objectPositionOrientation lego_dest;

/*---------------------------------------------function headers---------------------------------------------*/

void readParams(int argc, char **argv);
void defaultFunction();
void secureEnable();
void unknownUsage();     
bool handShake(); 
void subDetectCommanderCallback(const motion::legoFound::ConstPtr &msg_detect); // reception and analysis of a received request.
void pubDetectResulter(int risultato); // publish the result
void pubTaskCommander(bool s_ack); // publish the task 
void subTaskResulterCallback(const motion::eventResult::ConstPtr &msg_event); // read ack sent by movement

Eigen::Vector3f camera2SimulationR(Eigen::Vector3f simul_lego_pos); // adapt camera point values in virtual world for robot
Eigen::Vector3f camera2RealR(Eigen::Vector3f camera_lego_pos); // adapt camera point values in real world for robot
void ungraspCommand(); // Enlarge robot fingers
void homingCommand(); // move the arm to default to avoid camera interferences

void catchCommand(Eigen::Vector3f position); // send the complete catch command to the moviment module

void selectClass(int lego_cl);  // In relation to lego received from vision, load right lego parameters
double getTimeNow(); // Returns the current time
double getInterval(double start_t); // Returns the difference between the currentTime and the start time

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

        cout << "----------------------------------------------" << endl;
        cout << "Default function selected: NO SECURITY" << endl;
        cout << "----------------------------------------------" << endl;
}

void secureEnable() {

        security_flag = true;

        cout << "----------------------------------------------" << endl;
        cout << "Security ON" << endl;
        cout << "----------------------------------------------" << endl;

        if (handShake()) {

                ///////////////////////////////////

        } else {

                ///////////////////////////////////

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

        ////////////////////////////////////////

        return true;

}

/*---------------------------------------------Implemented functions---------------------------------------------*/

void subDetectCommanderCallback(const motion::legoFound::ConstPtr &msg_detect) {

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

                if (verbose_flag) cout << "---------------------------------------" << endl;
                if (verbose_flag) cout << "Subscriber: " << sub_detect_commander << " receved some data:" << endl;      
                if (verbose_flag) cout << "---------------------------------------" << endl;   
                if (verbose_flag) cout << "Command ID " << msg_detect->command_id << endl;
                if (verbose_flag) cout << "Send ack: " << msg_detect->send_ack << endl;
                if (verbose_flag) cout << "Lego class: " << msg_detect->lego_class << endl;
                if (verbose_flag) cout << "X coordinate: " << msg_detect->coord_x << endl;
                if (verbose_flag) cout << "Y coordinate: " << msg_detect->coord_y << endl;
                if (verbose_flag) cout << "Z coordinate: " << msg_detect->coord_z << endl;
                if (verbose_flag) cout << "Roll orientation: " << msg_detect->rot_roll << endl;
                if (verbose_flag) cout << "Pitch orientation: " << msg_detect->rot_pitch << endl;
                if (verbose_flag) cout << "Yaw orientation: " << msg_detect->rot_yaw << endl;
                if (verbose_flag) cout << "---------------------------------------" << endl;
                
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

        if (verbose_flag) cout << "---------------------------------------" << endl;
        if (verbose_flag) cout << "Publisher: " << pub_detect_resulter << " sent some data:" << endl;
        if (verbose_flag) cout << "---------------------------------------" << endl;
        if (verbose_flag) cout << "Event ID: " << msg_evento_detect.event_id << endl;
        if (verbose_flag) cout << "Result ID: " << msg_evento_detect.result_id << endl;
        if (verbose_flag) cout << "---------------------------------------" << endl;
}

void pubTaskCommander(bool s_ack) {

        msg_taskCommand.send_ack = s_ack;
        pub_task_commander_handle.publish(msg_taskCommand);

        if (verbose_flag) cout << "---------------------------------------" << endl;
        if (verbose_flag) cout << "Publisher: " << pub_task_commander << " sent some data:" << endl;
        if (verbose_flag) cout << "---------------------------------------" << endl;
        if (verbose_flag) cout << "Command ID: " << msg_taskCommand.command_id << endl;
        if (verbose_flag) cout << "Ack: " << msg_taskCommand.send_ack << endl;
        if (verbose_flag) cout << "Wait time: " << msg_taskCommand.w_time << endl;       
        if (verbose_flag) cout << "Is real robot: " << msg_taskCommand.real_robot << endl;
        if (verbose_flag) cout << "X coordinate: " << msg_taskCommand.coord_x << endl;
        if (verbose_flag) cout << "Y coordinate: " << msg_taskCommand.coord_y << endl;
        if (verbose_flag) cout << "Z coordinate: " << msg_taskCommand.coord_z << endl;
        if (verbose_flag) cout << "Roll orientation: " << msg_taskCommand.rot_roll << endl;
        if (verbose_flag) cout << "Pitch orientation: " << msg_taskCommand.rot_pitch << endl;
        if (verbose_flag) cout << "Yaw orientation: " << msg_taskCommand.rot_yaw << endl;
        if (verbose_flag) cout << "Lego grasp diameter: " << msg_taskCommand.gasp_diam << endl;
        if (verbose_flag) cout << "X destination coordinate: " << msg_taskCommand.dest_x << endl;
        if (verbose_flag) cout << "Y destination coordinate: " << msg_taskCommand.dest_y << endl;
        if (verbose_flag) cout << "Z destination coordinate: " << msg_taskCommand.dest_z << endl;
        if (verbose_flag) cout << "Roll destination orientation: " << msg_taskCommand.dest_roll << endl;
        if (verbose_flag) cout << "Pitch destination orientation: " << msg_taskCommand.dest_pitch << endl;
        if (verbose_flag) cout << "Yaw destination orientation: " << msg_taskCommand.dest_yaw << endl;
        if (verbose_flag) cout << "Lego ungasp diameter " << msg_taskCommand.ungasp_diam << endl; 
        if (verbose_flag) cout << "---------------------------------------" << endl;

        if (s_ack) {

                movement_task.command_id = msg_taskCommand.command_id;
                movement_task.process_time = getTimeNow();
                movement_task.busy = true;

                if (verbose_flag) cout << "Processo " << movement_task.command_id << " messo in attesa" << endl;
        
        } else {

                movement_task.busy = false;                
        }        
}

void subTaskResulterCallback(const motion::eventResult::ConstPtr &msg_event) {

        msg_evento_task.event_id = msg_event->event_id;
        msg_evento_task.result_id = msg_event->result_id;

        if (verbose_flag) cout << "---------------------------------------" << endl;
        if (verbose_flag) cout << "Subscriber: " << sub_task_resulter << " receved some data:" << endl;
        if (verbose_flag) cout << "---------------------------------------" << endl;
        if (verbose_flag) cout << "Event ID: " << msg_event->event_id << endl;
        if (verbose_flag) cout << "Result ID: " << msg_event->result_id << endl;
        if (verbose_flag) cout << "---------------------------------------" << endl;

        if (movement_task.busy) {

                if (movement_task.command_id == msg_evento_task.event_id) {

                        movement_task.busy = false;
                        movement_task.process_time = getInterval(movement_task.process_time);
                        if (verbose_flag) cout << "Processo " << movement_task.command_id << " completato" << endl;

                        cout << endl << " Movement process ID: " << movement_task.command_id << " KPI: " << movement_task.process_time << " seconds!" << endl;
                }
                
        }

        if (vision_task.busy) {

                if (msg_evento_task.event_id == command_catch && vision_task.command_id == command_detect) {

                        pubDetectResulter(msg_evento_task.result_id);
                        vision_task.busy = false;
                        vision_task.process_time = getInterval(vision_task.process_time);
                        if (verbose_flag) cout << "Task visione " << vision_task.command_id << " completato" << endl;

                        cout << endl << " Vision process ID: " << vision_task.command_id << " KPI: " << vision_task.process_time << " seconds!" << endl;
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

double getTimeNow() {
        ros::Time momento = ros::Time::now();        
        double tempo = momento.sec + (momento.nsec / 1000000);
        return tempo;
}

double getInterval(double start_t) {
        return (getTimeNow()- start_t);
}