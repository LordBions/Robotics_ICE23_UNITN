/*
*
* Authors: Filippo Conti, Mattia Meneghin e Nicola Gianuzzi
*
*/

#include <iostream>
#include <cmath>
#include <complex>
#include <Eigen/Dense>
#include "ros/ros.h"
#include "kinetics.h"
#include "motion/position.h"
#include <std_msgs/Int32.h>

using namespace std;

#define node_name "motion_planner"
#define pub_position_address "/motion/pos"
#define pub_ack_address "/vision/ack"
#define sub_vision_address "/vision/pos"          
#define sub_ack_address "/motion/ack"           
#define sub_stop_address "/planner/stop"

#define queque_size 10
#define loop_wait_rate 1000 
#define lego_coord_z 0.83
#define default_sim2bas_matrix 1, 0, 0, 0.5, 0, -1, 0, 0.35, 0, 0, -1, 1.75, 0, 0, 0, 1
#define default_cam2sim_matrix 0.866, 0, 0.5, -0.4, 0, 1, 0, 0.53, -0.5, 0, 0.866, 1.4, 0, 0, 0, 1


ros::Publisher pub_position_handle, pub_ack_handle; 
ros::Subscriber sub_vision_handle, sub_ack_handle, sub_stop_handle;      

bool is_real_robot = false;
bool is_vision_on = true;   
bool is_vision_msg_received = false;                
bool ready_flag = true;                         
bool stop_planner = false;                        

int lego_class;                        
Eigen::Vector3f lego_pos;             
Eigen::Vector3f lego_or;   
motion::position messaggio;

void pubPosition();
void subVisionCallback(const motion::position::ConstPtr &mex);
void subAckCallback(const std_msgs::Int32::ConstPtr &mex);
void subStopCallback(const std_msgs::Int32::ConstPtr &mex);
void pubAckPlanner();
Eigen::Vector3f simulation2base(Eigen::Vector3f simul_lego_pos);
Eigen::Vector3f camera2simulation(Eigen::Vector3f camera_lego_pos);

int main(int argc, char **argv) {

    cout << "Starting the planner module!" << endl;
    cout << "----------------------------" << endl << endl;
    
    ros::init(argc, argv, node_name);
    ros::NodeHandle node_handle;
    cout << "Node: " << node_name << " initialized!" << endl;

    pub_position_handle = node_handle.advertise<motion::position>(pub_position_address, queque_size);
    cout << "Publisher: " << pub_position_address << " enabled with queque: " << queque_size << endl;

    pub_ack_handle = node_handle.advertise<std_msgs::Int32>(pub_ack_address, queque_size);
    cout << "Publisher: " << pub_ack_address << " enabled with queque: " << queque_size << endl;

    sub_vision_handle = node_handle.subscribe(sub_vision_address, queque_size, subVisionCallback);
    cout << "Subscriber: " << sub_vision_address << " enabled with queque: " << queque_size << endl;

    sub_ack_handle = node_handle.subscribe(sub_ack_address, queque_size, subAckCallback);
    cout << "Subscriber: " << sub_ack_address << " enabled with queque: " << queque_size << endl;
    
    sub_stop_handle = node_handle.subscribe(sub_stop_address, queque_size, subStopCallback);
    cout << "Subscriber: " << sub_stop_address << " enabled with queque: " << queque_size << endl;

    cout << "----------------------------" << endl << endl;
    ros::Rate loop_rate(loop_wait_rate);

    while (ros::ok()) {

        while (pub_position_handle.getNumSubscribers() < 1) { loop_rate.sleep(); }
                        
        if (!is_vision_on) {                 
        
            if (ready_flag) {             
            
                ready_flag = false;

                cout << "Insert the lego class: ";
                cin >> messaggio.lego_class;

                cout << "Insert the position (x y z roll pitch yaw): ";
                cin >> messaggio.coord_x >> messaggio.coord_y >> messaggio.coord_z >> messaggio.rot_roll >> messaggio.rot_pitch >> messaggio.rot_yaw;

                pubPosition();

            }

        } else {                                    
        
            if (is_vision_msg_received && ready_flag && !stop_planner) {     
                
                ready_flag = false;

                if (is_real_robot) {                    
                    lego_pos = camera2simulation(lego_pos);
                } else {
                    lego_pos = simulation2base(lego_pos);
                }

                messaggio.lego_class = lego_class;

                messaggio.coord_x = lego_pos(0);
                messaggio.coord_y = lego_pos(1);
                messaggio.coord_z = lego_coord_z;

                messaggio.rot_roll = lego_or(0);
                messaggio.rot_pitch = lego_or(1);
                messaggio.rot_yaw = lego_or(2);

                pubPosition();
            }
        }

        ros::spinOnce();

    }

    cout << endl;
    cout << "Exit process invoked!" << endl;
    return 0;
    
}

void pubPosition() {

    cout << endl;

    pub_position_handle.publish(messaggio);
    is_vision_msg_received = false;

    cout << "Publisher: " << pub_position_address << " sent some data:" << endl;
    cout << "Lego class: " << messaggio.lego_class << endl;

    cout << "X coordinate: " << messaggio.coord_x << endl;
    cout << "Y coordinate: " << messaggio.coord_y << endl;
    cout << "Z coordinate: " << messaggio.coord_z << endl;

    cout << "Roll orientation: " << messaggio.rot_roll << endl;
    cout << "Pitch orientation: " << messaggio.rot_pitch << endl;
    cout << "Yaw orientation: " << messaggio.rot_yaw << endl;

    cout << endl;
}

void subVisionCallback(const motion::position::ConstPtr &mex) {

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

void subAckCallback(const std_msgs::Int32::ConstPtr &mex) {

    cout << endl;
    cout << "Subscriber: " << sub_ack_address << " receved some data:" << endl;

    ready_flag = mex->data;
    cout << "Ready flag: " << ready_flag << endl;
    
    pubAckPlanner();

    cout << endl;
}

void subStopCallback(const std_msgs::Int32::ConstPtr &mex) {

    cout << endl;
    cout << "Subscriber: " << sub_stop_address << " receved some data:" << endl;

    stop_planner = mex->data;
    cout << "Stop command: " << stop_planner << endl;

    cout << endl;
}

void pubAckPlanner() {

    cout << endl;

    ros::Rate loop_rate(loop_wait_rate);

    std_msgs::Int32 ackP_msg;
    ackP_msg.data = true;
    pub_ack_handle.publish(ackP_msg);

    cout << "Publisher: " << pub_ack_address << " sent some data:" << endl;
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