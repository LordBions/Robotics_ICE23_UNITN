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
#include "motion/pos.h"
#include <std_msgs/Int32.h>

using namespace std;

#define node_name "motion_planner"
#define pub_position_address "/motion/pos"
#define pub_position_ack_address "/vision/ack"
#define sub_vision_address "/vision/pos"          
#define sub_position_ack_address "/motion/ack"           
#define sub_stop_address "/planner/stop"

#define queque_size 10
#define loop_wait_rate 1000 

ros::Publisher pub_position_handle, pub_position_ack_handle; 
ros::Subscriber sub_vision_handle, sub_position_ack_handle, sub_stop_handle;      

bool is_real_robot = false;
bool is_vision_on = true;   
bool is_vision_msg_received = false;                
bool ready_flag = true;                         
bool stop_planner = false;                        

int block_class;                        // Class of the block
Eigen::Vector3f block_pos;              // Position of the block
Eigen::Vector3f block_rot;              // Rotation of the block

Eigen::Vector3f worldToBase(Eigen::Vector3f xw);
Eigen::Vector3f cameraToWorld(Eigen::Vector3f xw);
void visionCallback(const motion::pos::ConstPtr &msg);
void ackCallback(const std_msgs::Int32::ConstPtr &msg);
void stopCallback(const std_msgs::Int32::ConstPtr &msg);
void ack();

int main(int argc, char **argv) {

    cout << "Starting the planner module!" << endl;
    cout << "----------------------------" << endl << endl;
    
    ros::init(argc, argv, node_name);
    ros::NodeHandle node_handle;
    cout << "Node: " << node_name << " initialized!" << endl;

    pub_position_handle = node_handle.advertise<motion::pos>(pub_position_address, queque_size);
    cout << "Publisher: " << pub_position_address << " enabled with queque: " << queque_size << endl;

    pub_position_ack_handle = node_handle.advertise<std_msgs::Int32>(pub_position_ack_address, queque_size);
    cout << "Publisher: " << pub_position_ack_address << " enabled with queque: " << queque_size << endl;

    sub_vision_handle = node_handle.subscribe(sub_vision_address, queque_size, visionCallback);
    cout << "Subscriber: " << sub_vision_address << " enabled with queque: " << queque_size << endl;

    sub_position_ack_handle = node_handle.subscribe(sub_position_ack_address, queque_size, ackCallback);
    cout << "Subscriber: " << sub_position_ack_address << " enabled with queque: " << queque_size << endl;
    
    sub_stop_handle = node_handle.subscribe(sub_stop_address, queque_size, stopCallback);
    cout << "Subscriber: " << sub_stop_address << " enabled with queque: " << queque_size << endl;
    cout << "----------------------------" << endl << endl;

    ros::Rate loop_rate(loop_wait_rate);

    motion::pos msg;

    while (ros::ok()) {

        while (pub_position_handle.getNumSubscribers() < 1) {

            loop_rate.sleep();
        }
                        
        if (!is_vision_on) {            // If the vision is not on, the user has to insert the position of the block        
        
            if (ready_flag) {             // If the motion is finished, the user can insert the position of the block
            
                ready_flag = false;

                cout << "Insert the position (x y z roll pitch yaw): ";
                cin >> msg.coord_x >> msg.coord_y >> msg.coord_z >> msg.rot_roll >> msg.rot_pitch >> msg.rot_yaw;
                
                cout << "Insert the lego class: ";
                cin >> msg.lego_class;

                pub_position_handle.publish(msg);
            }
        }
        else {                                    // Vision is on
        
            if (is_vision_msg_received && ready_flag && !stop_planner) {        // If vision msg is received and the motion is finished, send the position to the motion
                
                ready_flag = false;

                cout << "Blocks coordinates received from vision" << endl;
                cout << "Block class: " << block_class << endl;
                cout << "Block position: " << block_pos.transpose() << endl;
                cout << "Block rotation: " << block_rot.transpose() << endl << endl;

                if (is_real_robot) {                    
                    block_pos = cameraToWorld(block_pos);
                }                    
                else {
                    block_pos = worldToBase(block_pos);
                }

                msg.lego_class = block_class;

                msg.coord_x = block_pos(0);
                msg.coord_y = block_pos(1);
                msg.coord_z = 0.82;

                msg.rot_roll = block_rot(0);
                msg.rot_pitch = block_rot(1);
                msg.rot_yaw = block_rot(2);

                is_vision_msg_received = false;
                pub_position_handle.publish(msg);
            }
        }

        ros::spinOnce();

    }

}

/**
 * @brief Convert the position of the block from the world frame to the base frame
 * 
 * @param xw 3D vector representing the position of the block in the world frame
 * @return Vector3f 
 */
Eigen::Vector3f worldToBase(Eigen::Vector3f xw) {

    Eigen::Matrix4f T;
    Eigen::Vector3f xb;
    Eigen::Vector4f xt;
    
    T << 1, 0, 0, 0.5, 0, -1, 0, 0.35, 0, 0, -1, 1.75, 0, 0, 0, 1;
    xt = T.inverse() * Eigen::Vector4f(xw(0), xw(1), xw(2), 1);
    xb << xt(0), xt(1), xt(2);

    return xb;
}

/**
 * @brief Convert the position of the block from the camera frame (real robot) to the world frame
 * 
 * @param xw 3D vector representing the position of the block in the camera frame
 * @return Vector3f 
 */

Eigen::Vector3f cameraToWorld(Eigen::Vector3f xw) {

    Eigen::Matrix4f T;
    Eigen::Vector3f xb;
    Eigen::Vector4f xt;
    
    T << 0.866, 0, 0.5, -0.4, 0, 1, 0, 0.53, -0.5, 0, 0.866, 1.4, 0, 0, 0, 1;
    xt = T * Eigen::Vector4f(xw(0), xw(1), xw(2), 1);
    xb << xt(0), xt(1), xt(2);

    return xb;
}

/**
 * @brief Callback function for the vision topic, sets the detected position of the block
 * 
 * @param msg message received
 */
void visionCallback(const motion::pos::ConstPtr &msg) {

    is_vision_msg_received = true;                      
    
    block_pos << msg->coord_x, msg->coord_y, msg->coord_z;
    block_rot << msg->rot_roll, msg->rot_pitch, msg->rot_yaw;
    block_class = msg->lego_class;
}

/**
 * @brief Callback function for the ack topic, sets the ready variable -> finished the motion
 * 
 * @param msg message received
 */
void ackCallback(const std_msgs::Int32::ConstPtr &msg) {

    ready_flag = msg->data;
    ack();
}

/**
 * @brief     This function is used to send the ack to the taskManager
 *              - send it when the robot has finished the motion task
 * 
 */
void ack() {

    ros::Rate loop_rate(loop_wait_rate);
    std_msgs::Int32 ack;
    ack.data = 1;
    pub_position_ack_handle.publish(ack);
}

/**
 * @brief Callback function for the stop topic, sets the stop variable -> stop the motion -> finished the task
 * 
 * @param msg 
 */
void stopCallback(const std_msgs::Int32::ConstPtr &msg) {

    stop_planner = msg->data;
}
