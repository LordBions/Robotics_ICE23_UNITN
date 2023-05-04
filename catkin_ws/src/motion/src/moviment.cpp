/*
* Authors: Filippo Conti, Mattia Meneghin e Nicola Gianuzzi
*/

#include <iostream>
#include <cmath>
#include <complex>
#include <Eigen/Dense>
#include "ros/ros.h"
#include "kinetics.h"
#include "motion/position.h"
#include <std_msgs/Int32.h>
#include <std_msgs/Float64MultiArray.h>
#include <ros_impedance_controller/generic_float.h>

using namespace std;

#define node_name "ur5_arm_publisher"
#define pub_joint_address "/ur5/joint_group_pos_controller/command"
#define pub_position_ack_address "/motion/position_ack"
#define sub_position_address "/motion/pos"
#define client_gripper_address "/move_gripper"

#define queque_size 10
#define loop_wait_rate 1000 
#define joint_number 9
#define default_target_position -0.4, -0.4, 0.4 // x, y z
#define default_joint_state_vector -0.32, -0.78, -2.56, -1.63, -1.57, 3.49
#define default_dt 0.001
#define default_max_traj_time 6
#define sleep_time 50
#define position_gain 5
#define orientation_gain 30
#define half_point 0, -0.4, 0.6
#define grasp_value 45
#define no_grasp_value 100
#define null_vector 0, 0, 0
#define z_above_object 0.6

#define class_00_relocation 0.4, -0.00, 0.82
#define class_01_relocation 0.4, -0.05, 0.82
#define class_02_relocation 0.4, -0.10, 0.82
#define class_03_relocation 0.4, -0.15, 0.82
#define class_04_relocation 0.4, -0.20, 0.82
#define class_05_relocation 0.4, -0.25, 0.82
#define class_06_relocation 0.4, -0.30, 0.82
#define class_07_relocation 0.4, -0.35, 0.82
#define class_08_relocation 0.4, -0.40, 0.82
#define class_09_relocation 0.4, -0.45, 0.82
#define class_10_relocation 0.4, -0.50, 0.82

ros::Publisher pub_joint_handle, pub_position_ack_handle;
ros::Subscriber sub_position_handle;
ros::ServiceClient client_gripper_handle;
				    
bool is_real_robot = false;	
bool grasp_flag = false;
bool initial_state = true;			        
int lego_class;		

struct objectPositionOrientation {
    Eigen::Vector3f position;
    Eigen::Vector3f orientation;
};

objectPositionOrientation obj_pos_or; 	
					                      
Eigen::VectorXf joint_state_vector(6);				        				                
double max_trajectory_time = default_max_traj_time;		     

void moveDefaultPosition();
void moveProcedure(Eigen::Vector3f v_position, Vector3f v_orientation, float dt);
Eigen::Vector3f getTrajectory(double time, Eigen::Vector3f final_position, Eigen::Vector3f begin_position);
Eigen::VectorXf inverseSpeedKinematic(Eigen::VectorXf joint_st, Eigen::Vector3f curr_position, Eigen::Vector3f destin_position, Eigen::Vector3f velocity, Eigen::Matrix3f curr_orientation, Eigen::Vector3f final_orientation);
Eigen::Vector3f correctOrientation(Matrix3f final_orientation, Matrix3f curr_orientation);
void updateJointStates(Eigen::VectorXf q);
float gripper2joints(float diameter);
void subscriberCallback(const motion::position::ConstPtr &mex);
void catchProcedure();
void graspObject();
Eigen::Vector3f selectClassDesitnation(int lego_cl);
void pubReadyACK();
void waitForAWhile();

int main(int argc, char **argv) {

    cout << "Starting the moviment module!" << endl;
    cout << "----------------------------" << endl << endl;

    ros::init(argc, argv, node_name);
    ros::NodeHandle node_handle;
    cout << "Node: " << node_name << " initialized!" << endl;
   
    pub_joint_handle = node_handle.advertise<std_msgs::Float64MultiArray>(pub_joint_address, queque_size);
    cout << "Publisher: " << pub_joint_address << " enabled with queque: " << queque_size << endl;
    
    pub_position_ack_handle = node_handle.advertise<std_msgs::Int32>(pub_position_ack_address, queque_size);
    cout << "Publisher: " << pub_position_ack_address << " enabled with queque: " << queque_size << endl;

    sub_position_handle = node_handle.subscribe(sub_position_address, queque_size, subscriberCallback);
    cout << "Subscriber: " << sub_position_address << " enabled with queque: " << queque_size << endl;

    client_gripper_handle = node_handle.serviceClient<ros_impedance_controller::generic_float>(client_gripper_address);
    cout << "Service client: " << client_gripper_address << " enabled!" << endl;
    cout << "----------------------------" << endl << endl;

    joint_state_vector << default_joint_state_vector;

    moveDefaultPosition();

    cout << "Moviment module ready!" << endl;
    while (ros::ok()) { ros::spinOnce(); }

    cout << endl << "Exit process invoked!" << endl;
    return 0;
}

void moveDefaultPosition() {

    cout << "Moving the UR5 arm to default position..." << endl;

    Vector3f default_pos_vector;
    default_pos_vector << default_target_position;

    moveProcedure(default_pos_vector, obj_pos_or.orientation, default_dt);

    cout << "UR5 reached the default position!" << endl;
}

void moveProcedure(Eigen::Vector3f v_position, Eigen::Vector3f v_orientation, float dt) {

    frame start_frame, current_frame;

    if  (initial_state) {
        joint_state_vector << default_joint_state_vector; 
        initial_state = false;
    }

    start_frame = directKin(joint_state_vector);

    Eigen::VectorXf qk = joint_state_vector;           // set the initial joint config
    Eigen::VectorXf qk1(6);             // joint config

    Eigen::Matrix3f kp; // position gain
    kp = Eigen::Matrix3f::Identity() * position_gain;

    Eigen::Matrix3f kphi; // orientation gain
    kphi = Eigen::Matrix3f::Identity() * orientation_gain;

    Eigen::VectorXf dotqk(6); // joint velocities coefficients

    Eigen::Vector3f velocity; // desired linear velocity     // get the inverse kinematics matrix

    for (double i = dt; i <= max_trajectory_time; i += dt) {

        current_frame = directKin(qk); // get the current frame

        velocity = (getTrajectory(i, v_position, start_frame.xyz) - getTrajectory(i - dt, v_position, start_frame.xyz)) / dt; // desired linear velocity

        // coefficient
        dotqk = inverseSpeedKinematic(qk, current_frame.xyz, getTrajectory(i, v_position, start_frame.xyz), velocity, current_frame.rot, v_orientation);

        // euler integration
        qk1 = qk + dotqk * dt;
        qk = qk1;
        updateJointStates(qk);
    }

    joint_state_vector = qk;
}

Eigen::Vector3f getTrajectory(double time, Eigen::Vector3f final_position, Eigen::Vector3f begin_position) { // invertire parametri

    double t_norm = time / max_trajectory_time;

    if (t_norm > 1) {
        return final_position;
    } else {
        return t_norm * final_position + (1 - t_norm) * begin_position;
    }
}

Eigen::VectorXf inverseSpeedKinematic(Eigen::VectorXf joint_st, Eigen::Vector3f curr_position, Eigen::Vector3f destin_position, Eigen::Vector3f velocity, Eigen::Matrix3f curr_orientation, Eigen::Vector3f final_orientation) {

    float k = pow(10, -5); // damping coefficient
    Eigen::Matrix3f w_R_d = eul2rotm(final_orientation);
    Eigen::Vector3f error_o = correctOrientation(curr_orientation, w_R_d);
    
    Eigen::MatrixXf J;      // jacobian matrix
    J = jacobian(joint_st); // get the jacobian matrix
    Eigen::VectorXf qdot;
    Eigen::VectorXf ve(6);

    Eigen::Matrix3f kp; // position gain
    kp = Eigen::Matrix3f::Identity() * position_gain;

    Eigen::Matrix3f kphi; // orientation gain
    kphi = Eigen::Matrix3f::Identity() * orientation_gain;

    if (error_o.norm() > 1) {
        error_o = 0.1 * error_o.normalized();
    }

    ve << (velocity + kp * (destin_position - curr_position)), (kphi * error_o);
    qdot = (J + Eigen::MatrixXf::Identity(6, 6) * k).inverse() * ve;

    for (int i = 0; i < 6; i++) {

        if (qdot(i) > M_PI) {
            qdot(i) = 1.5;
        } else if (qdot(i) < -M_PI) {
            qdot(i) = -1.5;
        }
    }

    return qdot;
}

Eigen::Vector3f correctOrientation(Eigen::Matrix3f final_orientation, Eigen::Matrix3f curr_orientation) {
    
    Eigen::Matrix3f e_R_d = final_orientation.transpose() * curr_orientation; // compute relative orientation

    Eigen::Vector3f errorW;
    
    float cos_dtheta = (e_R_d(0, 0) + e_R_d(1, 1) + e_R_d(2, 2) - 1) / 2; // compute the delta angle
    Eigen::Vector3f axis;
    Eigen::MatrixXf aux(3, 2);
    aux << e_R_d(2, 1), -e_R_d(1, 2), e_R_d(0, 2), -e_R_d(2, 0), e_R_d(1, 0), -e_R_d(0, 1);
    
    float sin_dtheta = (pow(aux(0, 0), 2) + pow(aux(0, 1), 2) + pow(aux(1, 0), 2) + pow(aux(1, 1), 2) + pow(aux(2, 0), 2) + pow(aux(2, 1), 2)) * 0.5;

    float dtheta = atan2(sin_dtheta, cos_dtheta);
    
    if (dtheta == 0) {
        errorW << null_vector;
    } else {
        axis = 1 / (2 * sin_dtheta) * Vector3f(e_R_d(2, 1) - e_R_d(1, 2), e_R_d(0, 2) - e_R_d(2, 0), e_R_d(1, 0) - e_R_d(0, 1));
        errorW = final_orientation * dtheta * axis;
    }

    return errorW;
}

void updateJointStates(Eigen::VectorXf joint_st) {

    ros::Rate wait_loop(loop_wait_rate);	
    std_msgs::Float64MultiArray jointState_msg_robot;
    jointState_msg_robot.data.resize(joint_number);
    
    for (int i = 0; i < 6; i++) {
        jointState_msg_robot.data[i] = joint_st(i);
    }
    
    jointState_msg_robot.data[5] = 3.49;
    
    if (!is_real_robot) {

        if (grasp_flag) {            
            jointState_msg_robot.data[6] = gripper2joints(grasp_value);
            jointState_msg_robot.data[7] = gripper2joints(grasp_value);
            jointState_msg_robot.data[8] = gripper2joints(grasp_value);
        }

        else {
        
            jointState_msg_robot.data[6] = gripper2joints(no_grasp_value);
            jointState_msg_robot.data[7] = gripper2joints(no_grasp_value);
            jointState_msg_robot.data[8] = gripper2joints(no_grasp_value);
        }
    }

    pub_joint_handle.publish(jointState_msg_robot);
    wait_loop.sleep();
}

float gripper2joints(float diameter) {

    return (float) (diameter - 22) / (130 - 22) * (-M_PI) + M_PI;
}

void subscriberCallback(const motion::position::ConstPtr &mex) {

    cout << endl;
    cout << "Subscriber: " << sub_position_address << " receved some data:" << endl;

    lego_class = mex->lego_class;
    cout << "Lego class: " << lego_class << endl;

    obj_pos_or.position(0) = mex->coord_x;
    cout << "X coordinate: " << obj_pos_or.position(0) << endl;
    obj_pos_or.position(1) = mex->coord_y;
    cout << "Y coordinate: " << obj_pos_or.position(1) << endl;
    obj_pos_or.position(2) = mex->coord_z;
    cout << "Z coordinate: " << obj_pos_or.position(2) << endl;

    obj_pos_or.orientation(0) = mex->rot_roll;
    cout << "Roll orientation: " << obj_pos_or.orientation(0) << endl;
    obj_pos_or.orientation(1) = mex->rot_pitch;
    cout << "Pitch orientation: " << obj_pos_or.orientation(1) << endl;
    obj_pos_or.orientation(2) = mex->rot_yaw;
    cout << "Yaw orientation: " << obj_pos_or.orientation(2) << endl << endl; 
    
    catchProcedure();    
}

void catchProcedure() {
    
    Eigen::Vector3f destination;
    cout << "Starting the catch procedure..." << endl;

    destination << obj_pos_or.position(0), obj_pos_or.position(1), z_above_object;
    moveProcedure(destination, obj_pos_or.orientation, default_dt);
    cout << "UR5 arm is above the object!" << endl;

    destination << obj_pos_or.position(0), obj_pos_or.position(1), obj_pos_or.position(2);		
    moveProcedure(destination, obj_pos_or.orientation, default_dt);
    cout << "UR5 arm is on the object" << endl;

    grasp_flag = true;	
    graspObject();
    cout << "Keeping fingers closed..." << endl;
    
    destination << half_point;			    
    moveProcedure(destination, obj_pos_or.orientation, default_dt);           
    cout << "UR5 arm reached the half point" << endl;
    
    destination = selectClassDesitnation(lego_class);        
    moveProcedure(destination, obj_pos_or.orientation, default_dt);
    cout << "UR5 arm reached the class relocation position" << endl;

    grasp_flag = false;			     
    graspObject();
    cout << "Keeping fingers open..." << endl;
    
    destination(2) = z_above_object;		
    moveProcedure(destination, obj_pos_or.orientation, default_dt);
    cout << "UR5 arm is above the class relocation position!" << endl;

    updateJointStates(joint_state_vector);
    
    destination << half_point;	  
    moveProcedure(destination, obj_pos_or.orientation, default_dt);
    cout << "UR5 arm reached the half point" << endl;
    
    moveDefaultPosition();

    pubReadyACK();

    cout << "Catch procedure terminated" << endl << endl;
}

void graspObject() {

    ros_impedance_controller::generic_float gripper_diameter;
    ros::Rate wait_loop(loop_wait_rate);	

    if (is_real_robot) {

        cout << "Real robot grasp:" << endl;
        
        if (grasp_flag) {

            cout << "closing UR5 fingers..." << endl;
            gripper_diameter.request.data = 60;
            client_gripper_handle.call(gripper_diameter);
            cout << "UR5 fingers closed, possibly arround the object!" << endl;

        } else {

            cout << "Opening UR5 fingers..." << endl;
            gripper_diameter.request.data = 100;
            client_gripper_handle.call(gripper_diameter);
            cout << "UR5 fingers opened, possibly relased object!" << endl;
        }

    } else {

        cout << "Virtual robot grasp!" << endl;
        updateJointStates(joint_state_vector);
    }

    for (int i = 0; i < sleep_time; i++) { 
        wait_loop.sleep();
    }
}

Eigen::Vector3f selectClassDesitnation(int lego_cl) {

    Eigen::Vector3f destin;

    switch (lego_cl) {

        case 0: destin << class_00_relocation;
                break;

        case 1: destin << class_01_relocation;
                break;

        case 2: destin << class_02_relocation;
                break;

        case 3: destin << class_03_relocation;
                break;

        case 4: destin << class_04_relocation;
                break;

        case 5: destin << class_05_relocation;
                break;

        case 6: destin << class_06_relocation;
                break;

        case 7: destin << class_07_relocation;
                break;

        case 8: destin << class_08_relocation;
                break;

        case 9: destin << class_09_relocation;
                break;

        case 10: destin << class_10_relocation;

        default: break;
    }

    return destin;
}

void pubReadyACK() {

    std_msgs::Int32 ack_msg;
    ros::Rate wait_loop(loop_wait_rate);    
    ack_msg.data = true;
    
    for (int i = 0; i < sleep_time; i++) { 
        wait_loop.sleep();
    }
    
    pub_joint_handle.publish(ack_msg);

    cout << endl;
    cout << "Publisher: " << pub_joint_address << " sent some data:" << endl;
    cout << "Acknowledgment: " << ack_msg << endl << endl;
}