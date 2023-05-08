/*
* Authors: Filippo Conti, Mattia Meneghin e Nicola Gianuzzi
*/

#include <iostream>
#include <cmath>
#include <complex>
#include <Eigen/Dense>
#include "ros/ros.h"
#include "kinetics.h"
#include "motion/legoFound.h"
#include "motion/legoTask.h"
#include <std_msgs/Int32.h>

using namespace std;

#define node_name "motion_planner"
#define pub_taskCommander_address "/motion/taskCommander"
#define pub_plannerAck_address "/planner/readyACK"
#define sub_vision_address "/vision/legoDetector"          
#define sub_motionAck_address "/motion/readyACK"           
#define sub_plannerStop_address "/planner/stop"

#define command_catch 1
#define command_move 2
#define command_grasp 3
#define command_ungrasp 4

#define queque_size 10
#define loop_wait_rate 1000 

#define lego_coord_z 0.835
#define default_sim2bas_matrix 1, 0, 0, 0.5, 0, -1, 0, 0.35, 0, 0, -1, 1.75, 0, 0, 0, 1
#define default_cam2sim_matrix 0.866, 0, 0.5, -0.4, 0, 1, 0, 0.53, -0.5, 0, 0.866, 1.4, 0, 0, 0, 1

#define class_00_relocation 0.4, -0.000, 0.82
#define class_01_relocation 0.4, -0.046, 0.82
#define class_02_relocation 0.4, -0.092, 0.82
#define class_03_relocation 0.4, -0.138, 0.82
#define class_04_relocation 0.4, -0.022, 0.82
#define class_05_relocation 0.4, -0.230, 0.82
#define class_06_relocation 0.4, -0.276, 0.82
#define class_07_relocation 0.4, -0.322, 0.82
#define class_08_relocation 0.4, -0.368, 0.82
#define class_09_relocation 0.4, -0.414, 0.82
#define class_10_relocation 0.4, -0.460, 0.82

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

ros::Publisher pub_taskCommander_handle, pub_plannerAck_handle; 
ros::Subscriber sub_vision_handle, sub_motionAck_handle, sub_plannerStop_handle;      

bool is_real_robot = false;
bool manual_mode = false;   
bool is_vision_msg_received = false;                
bool ready_flag = true;                         
bool stop_planner = false; 
bool keep_orientation = false;                       

int lego_class;                        
Eigen::Vector3f lego_pos;             
Eigen::Vector3f lego_or;   
motion::legoTask msg_moviment;

Eigen::Vector3f dest_position;
Eigen::Vector3f dest_orientation;

void pubTaskCommander();
void catchCommand();
void selectClass(int lego_cl);
void subVisionCallback(const motion::legoFound::ConstPtr &mex);
void subMotionAckCallback(const std_msgs::Int32::ConstPtr &mex);
void subStopPlannerCallback(const std_msgs::Int32::ConstPtr &mex);
void pubAckPlanner();
Eigen::Vector3f simulation2base(Eigen::Vector3f simul_lego_pos);
Eigen::Vector3f camera2simulation(Eigen::Vector3f camera_lego_pos);

int main(int argc, char **argv) {

    cout << "Starting the planner module!" << endl;
    cout << "----------------------------" << endl << endl;
    
    ros::init(argc, argv, node_name);
    ros::NodeHandle node_handle;
    cout << "Node: " << node_name << " initialized!" << endl;

    pub_taskCommander_handle = node_handle.advertise<motion::legoTask>(pub_taskCommander_address, queque_size); 
    cout << "Publisher: " << pub_taskCommander_address << " enabled with queque: " << queque_size << endl;

    pub_plannerAck_handle = node_handle.advertise<std_msgs::Int32>(pub_plannerAck_address, queque_size);
    cout << "Publisher: " << pub_plannerAck_address << " enabled with queque: " << queque_size << endl;

    sub_vision_handle = node_handle.subscribe(sub_vision_address, queque_size, subVisionCallback);
    cout << "Subscriber: " << sub_vision_address << " enabled with queque: " << queque_size << endl;

    sub_motionAck_handle = node_handle.subscribe(sub_motionAck_address, queque_size, subMotionAckCallback);
    cout << "Subscriber: " << sub_motionAck_address << " enabled with queque: " << queque_size << endl;
    
    sub_plannerStop_handle = node_handle.subscribe(sub_plannerStop_address, queque_size, subStopPlannerCallback);
    cout << "Subscriber: " << sub_plannerStop_address << " enabled with queque: " << queque_size << endl;

    cout << "----------------------------" << endl << endl;
    ros::Rate loop_rate(loop_wait_rate);

    cout << "Motion planner ready!" << endl;

    while (ros::ok()) {

        while (pub_taskCommander_handle.getNumSubscribers() < 1) { loop_rate.sleep(); }
                        
        if (manual_mode) {                 
        
            if (ready_flag) {             
            
                ready_flag = false;

                cout << "Insert the command class: ";
                cin >> msg_moviment.command_id;

                cout << "Insert the begin position and orientation (x y z roll pitch yaw): ";
                cin >> msg_moviment.coord_x >> msg_moviment.coord_y >> msg_moviment.coord_z >> msg_moviment.rot_roll >> msg_moviment.rot_pitch >> msg_moviment.rot_yaw;

                cout << "Insert the grasp diameter: ";
                cin >> msg_moviment.gasp_diam;

                cout << "Insert the final position and orientation(x y z roll pitch yaw): ";
                cin >> msg_moviment.dest_x >> msg_moviment.dest_y >> msg_moviment.dest_z >> msg_moviment.dest_roll >> msg_moviment.dest_pitch >> msg_moviment.dest_yaw;

                pubTaskCommander();

            }

        } else {                                    
        
            if (is_vision_msg_received && ready_flag && !stop_planner) {     
                
                ready_flag = false;

                if (is_real_robot) { lego_pos = camera2simulation(lego_pos); }
                else { lego_pos = simulation2base(lego_pos); }

                catchCommand();
            }
        }

        ros::spinOnce();
    }

    cout << endl;
    cout << "Exit process invoked, closing planner module!" << endl;
    return 0;
    
}

void catchCommand() {

        msg_moviment.command_id = command_catch; // catch procedure

        msg_moviment.coord_x = lego_pos(0);
        msg_moviment.coord_y = lego_pos(1);
        msg_moviment.coord_z = lego_coord_z;

        msg_moviment.rot_roll = lego_or(0);
        msg_moviment.rot_pitch = lego_or(1);
        msg_moviment.rot_yaw = lego_or(2);

        selectClass(lego_class);

        pubTaskCommander();
}

void pubTaskCommander() {

    cout << endl;

    pub_taskCommander_handle.publish(msg_moviment);
    is_vision_msg_received = false;

    cout << "Publisher: " << pub_taskCommander_address << " sent some data:" << endl;
    cout << "Command ID: " << msg_moviment.command_id << endl;

    cout << "X coordinate: " << msg_moviment.coord_x << endl;
    cout << "Y coordinate: " << msg_moviment.coord_y << endl;
    cout << "Z coordinate: " << msg_moviment.coord_z << endl;

    cout << "Roll orientation: " << msg_moviment.rot_roll << endl;
    cout << "Pitch orientation: " << msg_moviment.rot_pitch << endl;
    cout << "Yaw orientation: " << msg_moviment.rot_yaw << endl;

    cout << "Lego grasp diameter: " << msg_moviment.gasp_diam << endl;

    cout << "X destination coordinate: " << msg_moviment.dest_x << endl;
    cout << "Y destination coordinate: " << msg_moviment.dest_y << endl;
    cout << "Z destination coordinate: " << msg_moviment.dest_z << endl;

    cout << "Roll destination orientation: " << msg_moviment.dest_roll << endl;
    cout << "Pitch destination orientation: " << msg_moviment.dest_pitch << endl;
    cout << "Yaw destination orientation: " << msg_moviment.dest_yaw << endl;

    cout << endl;
}

void selectClass(int lego_cl) {

    switch (lego_cl) {

        case 0: dest_position << class_00_relocation;
                break;

        case 1: dest_position << class_01_relocation;
                break;

        case 2: dest_position << class_02_relocation;
                break;

        case 3: dest_position << class_03_relocation;
                break;

        case 4: dest_position << class_04_relocation;
                break;

        case 5: dest_position << class_05_relocation;
                break;

        case 6: dest_position << class_06_relocation;
                break;

        case 7: dest_position << class_07_relocation;
                break;

        case 8: dest_position << class_08_relocation;
                break;

        case 9: dest_position << class_09_relocation;
                break;

        case 10: dest_position << class_10_relocation;

        default: break;
    }

    msg_moviment.dest_x = dest_position(0);
    msg_moviment.dest_y = dest_position(1);
    msg_moviment.dest_z = dest_position(2);

    if (keep_orientation) {

        msg_moviment.dest_roll = msg_moviment.rot_roll;
        msg_moviment.dest_pitch = msg_moviment.rot_pitch;
        msg_moviment.dest_yaw = msg_moviment.rot_yaw;

    } else {

        switch (lego_cl) {

            case 0: dest_orientation << class_00_orient;
                    break;

            case 1: dest_orientation << class_01_orient;
                    break;

            case 2: dest_orientation << class_02_orient;
                    break;

            case 3: dest_orientation << class_03_orient;
                    break;

            case 4: dest_orientation << class_04_orient;
                    break;

            case 5: dest_orientation << class_05_orient;
                    break;

            case 6: dest_orientation << class_06_orient;
                    break;

            case 7: dest_orientation << class_07_orient;
                    break;

            case 8: dest_orientation << class_08_orient;
                    break;

            case 9: dest_orientation << class_09_orient;
                    break;

            case 10: dest_orientation << class_10_orient;

            default: break;
        }

        msg_moviment.dest_roll = dest_orientation(0);
        msg_moviment.dest_pitch = dest_orientation(1);
        msg_moviment.dest_yaw = dest_orientation(2);

    }

    if (is_real_robot) {

        switch (lego_cl) {

            case 0: msg_moviment.gasp_diam = class_00_real_grasp;
                    break;

            case 1: msg_moviment.gasp_diam = class_01_real_grasp;
                    break;

            case 2: msg_moviment.gasp_diam = class_02_real_grasp;
                    break;

            case 3: msg_moviment.gasp_diam = class_03_real_grasp;
                    break;

            case 4: msg_moviment.gasp_diam = class_04_real_grasp;
                    break;

            case 5: msg_moviment.gasp_diam = class_05_real_grasp;
                    break;

            case 6: msg_moviment.gasp_diam = class_06_real_grasp;
                    break;

            case 7: msg_moviment.gasp_diam = class_07_real_grasp;
                    break;

            case 8: msg_moviment.gasp_diam = class_08_real_grasp;
                    break;

            case 9: msg_moviment.gasp_diam = class_09_real_grasp;
                    break;

            case 10: msg_moviment.gasp_diam = class_10_real_grasp;

            default: break;
        }

    } else {

        switch (lego_cl) {

            case 0: msg_moviment.gasp_diam = class_00_virt_grasp;
                    break;

            case 1: msg_moviment.gasp_diam = class_01_virt_grasp;
                    break;

            case 2: msg_moviment.gasp_diam = class_02_virt_grasp;
                    break;

            case 3: msg_moviment.gasp_diam = class_03_virt_grasp;
                    break;

            case 4: msg_moviment.gasp_diam = class_04_virt_grasp;
                    break;

            case 5: msg_moviment.gasp_diam = class_05_virt_grasp;
                    break;

            case 6: msg_moviment.gasp_diam = class_06_virt_grasp;
                    break;

            case 7: msg_moviment.gasp_diam = class_07_virt_grasp;
                    break;

            case 8: msg_moviment.gasp_diam = class_08_virt_grasp;
                    break;

            case 9: msg_moviment.gasp_diam = class_09_virt_grasp;
                    break;

            case 10: msg_moviment.gasp_diam = class_10_virt_grasp;

            default: break;
        }

    }

}

void subVisionCallback(const motion::legoFound::ConstPtr &mex) {

    is_vision_msg_received = true; 

    cout << endl;
    cout << "Subscriber: " << sub_vision_address << " receved some data:" << endl;                     
    
    lego_class = mex->lego_class;
    cout << "Lego class: " << lego_class << endl;

    lego_pos << mex->coord_x, mex->coord_y, mex->coord_z;
    cout << "X coordinate: " << mex->coord_x << endl;
    cout << "Y coordinate: " << mex->coord_y << endl;
    cout << "Z coordinate: " << mex->coord_z << endl;

    lego_or << mex->rot_roll, mex->rot_pitch, mex->rot_yaw;
    cout << "Roll orientation: " << mex->rot_roll << endl;
    cout << "Pitch orientation: " << mex->rot_pitch << endl;
    cout << "Yaw orientation: " << mex->rot_yaw << endl;

    cout << endl;
}

void subMotionAckCallback(const std_msgs::Int32::ConstPtr &mex) {

    cout << endl;
    cout << "Subscriber: " << sub_motionAck_address << " receved some data:" << endl;

    ready_flag = mex->data;
    cout << "Ready flag: " << ready_flag << endl;
    
    pubAckPlanner();

    cout << endl;
}

void subStopPlannerCallback(const std_msgs::Int32::ConstPtr &mex) {

    cout << endl;
    cout << "Subscriber: " << sub_plannerStop_address << " receved some data:" << endl;

    stop_planner = mex->data;
    cout << "Stop command: " << stop_planner << endl;

    cout << endl;
}

void pubAckPlanner() {

    cout << endl;

    ros::Rate loop_rate(loop_wait_rate);

    std_msgs::Int32 ackP_msg;
    ackP_msg.data = 1;
    pub_plannerAck_handle.publish(ackP_msg);

    cout << "Publisher: " << pub_plannerAck_address << " sent some data:" << endl;
    cout << "Acknowledgment: " << ackP_msg << endl;

    cout << endl;
}

Eigen::Vector3f simulation2base(Eigen::Vector3f simul_lego_pos) {

    Eigen::Matrix4f sim2bas_matrix;
    Eigen::Vector4f prod_vect;
    Eigen::Vector3f result_vect;
    
    sim2bas_matrix << default_sim2bas_matrix;
    prod_vect = sim2bas_matrix.inverse() * Eigen::Vector4f(simul_lego_pos(0), simul_lego_pos(1), simul_lego_pos(2), 1);
    result_vect << prod_vect(0), prod_vect(1), prod_vect(2);

    return result_vect;
}

Eigen::Vector3f camera2simulation(Eigen::Vector3f camera_lego_pos) {

    Eigen::Matrix4f cam2sim_matrix;
    Eigen::Vector4f prod_vect;
    Eigen::Vector3f result_vect;
    
    cam2sim_matrix << default_cam2sim_matrix;
    prod_vect = cam2sim_matrix * Eigen::Vector4f(camera_lego_pos(0), camera_lego_pos(1), camera_lego_pos(2), 1);
    result_vect << prod_vect(0), prod_vect(1), prod_vect(2);

    return result_vect;
}