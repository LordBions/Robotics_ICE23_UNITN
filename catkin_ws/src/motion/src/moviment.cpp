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
#define default_target_position -0.4, -0.4, 0.4
#define default_joint_state_vector -0.32, -0.78, -2.56, -1.63, -1.57, 3.49
#define default_dt 0.001

ros::Publisher pub_joint_handle, pub_position_ack_handle;
ros::Subscriber sub_position_handle;
ros::ServiceClient client_gripper_handle;
				    
bool is_real_robot = false;	
bool grasp_flag = false;
bool initial_state = true;			        
int lego_class;		

struct objectPositionOrientation {
    Vector3f position;
    Vector3f orientation;
};

objectPositionOrientation obj_pos_or; 	
					                      
Eigen::VectorXf joint_state_vector(6);				        				                
double max_trajectory_time = 6;				     

void defaultUR5Position();
void inverseDifferentialKinematic(Eigen::Vector3f xef, Vector3f phief, float dt);
Eigen::Vector3f getTrajectory(double t, Eigen::Vector3f xef, Eigen::Vector3f xe0);
Eigen::VectorXf inverseSpeedKinematic(Eigen::VectorXf q, Eigen::Vector3f xe, Eigen::Vector3f xd, Eigen::Vector3f vd, Eigen::Matrix3f w_R_e, Eigen::Vector3f phief);
Eigen::Vector3f correctOrientation(Matrix3f w_R_e, Matrix3f w_R_d);
void updateJointStates(Eigen::VectorXf q);
float gripper2joints(float diameter);
void subscriberCallback(const motion::position::ConstPtr &mex);
void moveProcedure();
void graspObject();
void pubReadyACK();

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

    joint_state_vector << -0.32, -0.78, -2.56, -1.63, -1.57, 3.49; // initial joint configuration

    cout << "Moving the UR5 arm to de default start position..." << endl;
    defaultUR5Position();

    cout << "Moviment module ready!" << endl;
    while (ros::ok()) { ros::spinOnce(); }

    cout << endl << "Exit process invoked!" << endl;
    return 0;
}

void defaultUR5Position() {

    cout << "Moving UR5 to default position..." << endl;

    Vector3f default_pos_vector;
    default_pos_vector << default_target_position;

    inverseDifferentialKinematic(default_pos_vector, obj_pos_or.orientation, default_dt);

    cout << "UR5 reached the default position!" << endl;
}

void inverseDifferentialKinematic(Eigen::Vector3f xef, Eigen::Vector3f phief, float dt) {

    frame start_frame, current_frame;

    if  (initial_state) {
         joint_state_vector << default_joint_state_vector; // initial joint configuration
    }

    initial_state = false;
    start_frame = directKin(joint_state_vector);

    VectorXf qk = joint_state_vector;           // set the initial joint config
    VectorXf qk1(6);             // joint config

    Matrix3f kp; // position gain
    kp = Eigen::Matrix3f::Identity() * 5;

    Matrix3f kphi; // orientation gain
    kphi = Eigen::Matrix3f::Identity() * 30;

    VectorXf dotqk(6); // joint velocities coefficients

    Vector3f vd; // desired linear velocity     // get the inverse kinematics matrix

    for (double i = dt; i <= max_trajectory_time; i += dt) {
        current_frame = directKin(qk); // get the current frame

        vd = (getTrajectory(i, xef, start_frame.xyz) - getTrajectory(i - dt, xef, start_frame.xyz)) / dt; // desired linear velocity

        // coefficient
        dotqk = inverseSpeedKinematic(qk, current_frame.xyz, getTrajectory(i, xef, start_frame.xyz), vd, current_frame.rot, phief);

        // euler integration
        qk1 = qk + dotqk * dt;
        qk = qk1;
        updateJointStates(qk);
    }
    joint_state_vector = qk;
}

Eigen::Vector3f getTrajectory(double t, Eigen::Vector3f xef, Eigen::Vector3f xe0) {

    double t_norm = t / max_trajectory_time;
    if (t_norm > 1) {
        return xef;
    }
    else {
        return t_norm * xef + (1 - t_norm) * xe0;
    }
}

Eigen::VectorXf inverseSpeedKinematic(Eigen::VectorXf q, Eigen::Vector3f xe, Eigen::Vector3f xd, Eigen::Vector3f vd, Eigen::Matrix3f w_R_e, Eigen::Vector3f phief) {

    float k = pow(10, -5); // damping coefficient
    Matrix3f w_R_d = eul2rotm(phief);
    Vector3f error_o = correctOrientation(w_R_e, w_R_d);
    
    MatrixXf J;      // jacobian matrix
    J = jacobian(q); // get the jacobian matrix
    VectorXf qdot;
    VectorXf ve(6);

    Matrix3f kp; // position gain
    kp = Eigen::Matrix3f::Identity() * 5;

    Matrix3f kphi; // orientation gain
    kphi = Eigen::Matrix3f::Identity() * 30;

    if (error_o.norm() > 1) {
        error_o = 0.1 * error_o.normalized();
    }

    ve << (vd + kp * (xd - xe)), (kphi * error_o);
    qdot = (J + Eigen::MatrixXf::Identity(6, 6) * k).inverse() * ve;

    for (int i = 0; i < 6; i++) {
        if (qdot(i) > M_PI) {
            qdot(i) = 1.5;
        }
        else if (qdot(i) < -M_PI) {
            qdot(i) = -1.5;
        }
    }

    return qdot;
}

Eigen::Vector3f correctOrientation(Eigen::Matrix3f w_R_e, Eigen::Matrix3f w_R_d) {
    
    Eigen::Matrix3f e_R_d = w_R_e.transpose() * w_R_d; // compute relative orientation

    Eigen::Vector3f errorW;
    
    float cos_dtheta = (e_R_d(0, 0) + e_R_d(1, 1) + e_R_d(2, 2) - 1) / 2; // compute the delta angle
    Vector3f axis;
    MatrixXf aux(3, 2);
    aux << e_R_d(2, 1), -e_R_d(1, 2), e_R_d(0, 2), -e_R_d(2, 0), e_R_d(1, 0), -e_R_d(0, 1);
    
    float sin_dtheta = (pow(aux(0, 0), 2) + pow(aux(0, 1), 2) + pow(aux(1, 0), 2) + pow(aux(1, 1), 2) + pow(aux(2, 0), 2) + pow(aux(2, 1), 2)) * 0.5;

    float dtheta = atan2(sin_dtheta, cos_dtheta);
    
    if (dtheta == 0) {
        errorW << 0, 0, 0;
    }
    else {
        axis = 1 / (2 * sin_dtheta) * Vector3f(e_R_d(2, 1) - e_R_d(1, 2), e_R_d(0, 2) - e_R_d(2, 0), e_R_d(1, 0) - e_R_d(0, 1));
        errorW = w_R_e * dtheta * axis;
    }

    return errorW;
}

void updateJointStates(Eigen::VectorXf q) {

    ros::Rate loop_rate(loop_wait_rate);
    std_msgs::Float64MultiArray jointState_msg_robot;
    jointState_msg_robot.data.resize(joint_number);
    
    for (int i = 0; i < 6; i++) {
        jointState_msg_robot.data[i] = q(i);
    }
    
    jointState_msg_robot.data[5] = 3.49;
    
    if (!is_real_robot) {
        if (grasp_flag) {            
            jointState_msg_robot.data[6] = gripper2joints(45);
            jointState_msg_robot.data[7] = gripper2joints(45);
            jointState_msg_robot.data[8] = gripper2joints(45);
        }
        else {
            jointState_msg_robot.data[6] = gripper2joints(100);
            jointState_msg_robot.data[7] = gripper2joints(100);
            jointState_msg_robot.data[8] = gripper2joints(100);
        }
    }

    pub_joint_handle.publish(jointState_msg_robot);
    loop_rate.sleep();
}

float gripper2joints(float diameter) {

    float alpha = (diameter - 22) / (130 - 22) * (-M_PI) + M_PI;
    return alpha;
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
    cout << "Yaw orientation: " << obj_pos_or.orientation(2) << endl; 
    
    moveProcedure();

    cout << endl;
}

void moveProcedure() {

    cout << "Starting the moving procedure..." << endl << endl;

    ros::Rate loop_rate(loop_wait_rate);

    float dt = default_dt;
    Vector3f target;
    target << obj_pos_or.position(0), obj_pos_or.position(1), 0.6;

    inverseDifferentialKinematic(target, obj_pos_or.orientation, dt);	                // go above the desired position

    target << obj_pos_or.position(0), obj_pos_or.position(1), obj_pos_or.position(2);		// go to the desired position
    inverseDifferentialKinematic(target, obj_pos_or.orientation, dt);

    grasp_flag = true;			   
    if (is_real_robot) {
        graspObject();
    }
    else {
        updateJointStates(joint_state_vector);
    }
    
    for (int i = 0; i < 50; i++) {
        loop_rate.sleep();
    }
    
    target << 0, -0.4, 0.6;			    // middle set point 
    
    inverseDifferentialKinematic(target, obj_pos_or.orientation, dt);
    
    switch (lego_class)	{
        case 0:
            target << 0.4, 0.0, 0.82;
            break;

        case 1:
            target << 0.4, -0.05, 0.82;
            break;

        case 2:
            target << 0.4, -0.1, 0.82;
            break;

        case 3:
            target << 0.4, -0.15, 0.82;
            break;

        case 4:
            target << 0.4, -0.20, 0.82;
            break;

        case 5:
            target << 0.4, -0.25, 0.82;
            break;

        case 6:
            target << 0.4, -0.30, 0.82;
            break;

        case 7:
            target << 0.4, -0.35, 0.82;
            break;

        case 8:
            target << 0.4, -0.40, 0.82;
            break;

        case 9:
            target << 0.3, -0.40, 0.82;
            break;

        case 10:
            target << 0.3, -0.35, 0.82;
            break;

        default:
            break;
        }
        
    inverseDifferentialKinematic(target, obj_pos_or.orientation, dt);

    grasp_flag = false;			  
    
    if (is_real_robot) {
        graspObject();
    }
    else {
        updateJointStates(joint_state_vector);
    }
    
    for (int i = 0; i < 50; i++) {
        loop_rate.sleep();
    }
    
    target(2) = 0.65;			// lift a little bit
    
    inverseDifferentialKinematic(target, obj_pos_or.orientation, dt);
    updateJointStates(joint_state_vector);
    
    target << 0, -0.4, 0.6;		// go to the middle point
    
    inverseDifferentialKinematic(target, obj_pos_or.orientation, dt);
    
    defaultUR5Position();		
    pubReadyACK();

    cout << "Moving procedure terminated" << endl << endl;
}

void graspObject() {

    ros_impedance_controller::generic_float gripper_diameter;
    if (grasp_flag) {
        gripper_diameter.request.data = 60;
        client_gripper_handle.call(gripper_diameter);
    }
    else {
        gripper_diameter.request.data = 100;
        client_gripper_handle.call(gripper_diameter);
    }
}

void pubReadyACK() {

    cout << endl;

    ros::Rate loop_rate(loop_wait_rate);
    std_msgs::Int32 ack_msg;
    ack_msg.data = true;
    
    for (int i = 0; i < 40; i++) { // wait a little bit before sending the ack 
        loop_rate.sleep();
    }
    
    pub_joint_handle.publish(ack_msg);

    cout << "Publisher: " << pub_joint_address << " sends some data:" << endl;
    cout << "Acknowledgment: " << ack_msg << endl;

    cout << endl;
}