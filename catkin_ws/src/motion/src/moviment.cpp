/*
*
* Authors: Filippo Conti, Mattia Meneghin e Nicola Gianuzzi
*
*/

#include "ros/ros.h"
#include "kinetics.h"
#include <Eigen/Dense>
#include <cmath>
#include <iostream>
#include "motion/pos.h"
#include <ros_impedance_controller/generic_float.h>
#include <complex>
#include <std_msgs/Float64MultiArray.h>
#include <std_msgs/Int32.h>

#define LOOP_RATE 1000 	// 1Hz
#define JOINTS 9

using namespace std;
using namespace Eigen;

struct Pose {
    Vector3f position;
    Vector3f orientation;
};

Pose pose; 					/// Position of the end-effector
int class_id;					/// Class of the block
int grasp = 0;					/// Flag to check if it have to grasp
ros::Publisher pub_des_jstate;		/// Publisher for the desired joint state
ros::Publisher ack_pos;			/// Publisher for the ack
ros::Subscriber sub_pos;			/// Subscriber for the position msg
ros::ServiceClient client;			/// Service call for the gripper
int real_robot = 0;				/// Flag to check if it is in simulation
VectorXf TH0(6);				/// @brief Initial joint configuration
int first = 1;					/// @brief Flag to check if it is the first time that the node is called
double maxT = 6;				/// @brief Max time for the trajectory

float mapToGripperJoints(float diameter);
Vector3f computeOrientationErrorW(Matrix3f w_R_e, Matrix3f w_R_d);
VectorXf invDiffKinematicControlComplete(VectorXf q, Vector3f xe, Vector3f xd, Vector3f vd, Matrix3f w_R_e, Vector3f phief);
Vector3f pd(double t, Vector3f xef, Vector3f xe0);
void invDiffKinematicControlSimComplete(Vector3f xef, Vector3f phief, float dt);
void posCallback(const motion::pos::ConstPtr &msg);
void sendJointState(VectorXf q);
void move();
void startingPosition();
void ack();
void graspit();

int main(int argc, char **argv)
{
    cout << "Running the moviment module!" << endl << endl;

    ros::init(argc, argv, "custom_joint_publisher");
    ros::NodeHandle node;

    pub_des_jstate = node.advertise<std_msgs::Float64MultiArray>("/ur5/joint_group_pos_controller/command", 1);
    ack_pos = node.advertise<std_msgs::Int32>("/motion/ack", 1);

    client = node.serviceClient<ros_impedance_controller::generic_float>("/move_gripper");

    sub_pos = node.subscribe("/motion/pos", 1, posCallback);

    TH0 << -0.32, -0.78, -2.56, -1.63, -1.57, 3.49; // initial joint configuration

    startingPosition();

    while (ros::ok())
    {
        ros::spinOnce();
    }
    return 0;
}

float mapToGripperJoints(float diameter) {
    float alpha = (diameter - 22) / (130 - 22) * (-M_PI) + M_PI;
    return alpha;
}

Vector3f computeOrientationErrorW(Matrix3f w_R_e, Matrix3f w_R_d) {
    
    Matrix3f e_R_d = w_R_e.transpose() * w_R_d; // compute relative orientation

    Vector3f errorW;
    
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

VectorXf invDiffKinematicControlComplete(VectorXf q, Vector3f xe, Vector3f xd, Vector3f vd, Matrix3f w_R_e, Vector3f phief) 
{
    float k = pow(10, -5); // damping coefficient
    Matrix3f w_R_d = eul2rotm(phief);
    Vector3f error_o = computeOrientationErrorW(w_R_e, w_R_d);
    
    MatrixXf J;      // jacobian matrix
    J = jacobian(q); // get the jacobian matrix
    VectorXf qdot;
    VectorXf ve(6);

    Matrix3f kp; // position gain
    kp = Matrix3f::Identity() * 5;

    Matrix3f kphi; // orientation gain
    kphi = Matrix3f::Identity() * 30;

    if (error_o.norm() > 1) {
        error_o = 0.1 * error_o.normalized();
    }

    ve << (vd + kp * (xd - xe)), (kphi * error_o);
    qdot = (J + MatrixXf::Identity(6, 6) * k).inverse() * ve;

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

Vector3f pd(double t, Vector3f xef, Vector3f xe0) {

    double t_norm = t / maxT;
    if (t_norm > 1) {
        return xef;
    }
    else {
        return t_norm * xef + (1 - t_norm) * xe0;
    }
}

void invDiffKinematicControlSimComplete(Vector3f xef, Vector3f phief, float dt) {

    frame now;   // current frame
    frame start; // start frame
    if  (first)
        TH0 << -0.32, -0.78, -2.56, -1.63, -1.57, 3.49; // initial joint configuration
    first = 0;
    start = directKin(TH0);

    VectorXf qk = TH0;           // set the initial joint config
    VectorXf qk1(6);             // joint config

    Matrix3f kp; // position gain
    kp = Matrix3f::Identity() * 5;

    Matrix3f kphi; // orientation gain
    kphi = Matrix3f::Identity() * 30;

    VectorXf dotqk(6); // joint velocities coefficients

    Vector3f vd; // desired linear velocity     // get the inverse kinematics matrix

    // loop
    for (double i = dt; i <= maxT; i += dt) {
        now = directKin(qk); // get the current frame

        vd = (pd(i, xef, start.xyz) - pd(i - dt, xef, start.xyz)) / dt; // desired linear velocity

        // coefficient
        dotqk = invDiffKinematicControlComplete(qk, now.xyz, pd(i, xef, start.xyz), vd, now.rot, phief);

        // euler integration
        qk1 = qk + dotqk * dt;
        qk = qk1;
        sendJointState(qk);
    }
    TH0 = qk;
}

void posCallback(const motion::pos::ConstPtr &msg) {

    pose.position(0) = msg->x;
    pose.position(1) = msg->y;
    pose.position(2) = msg->z;

    pose.orientation(0) = msg->roll;
    pose.orientation(1) = msg->pitch;
    pose.orientation(2) = msg->yaw;

    class_id = msg->class_id;

    move();
}

void sendJointState(VectorXf q)
{
    ros::Rate loop_rate(LOOP_RATE);
    std_msgs::Float64MultiArray jointState_msg_robot;
    jointState_msg_robot.data.resize(JOINTS);
    
    for (int i = 0; i < 6; i++) {
        jointState_msg_robot.data[i] = q(i);
    }
    
    jointState_msg_robot.data[5] = 3.49;
    
    if (!real_robot) {
        if (grasp) {            
            jointState_msg_robot.data[6] = mapToGripperJoints(45);
            jointState_msg_robot.data[7] = mapToGripperJoints(45);
            jointState_msg_robot.data[8] = mapToGripperJoints(45);
        }
        else {
            jointState_msg_robot.data[6] = mapToGripperJoints(100);
            jointState_msg_robot.data[7] = mapToGripperJoints(100);
            jointState_msg_robot.data[8] = mapToGripperJoints(100);
        }
    }

    pub_des_jstate.publish(jointState_msg_robot);
    loop_rate.sleep();
}

void move() {

    ros::Rate loop_rate(LOOP_RATE);

    float dt; // time step
    dt = 0.001;
    Vector3f target;
    target << pose.position(0), pose.position(1), .6;

    invDiffKinematicControlSimComplete(target, pose.orientation, dt);	    // go above the desired position

    target << pose.position(0), pose.position(1), pose.position(2);		    // go to the desired position
    invDiffKinematicControlSimComplete(target, pose.orientation, dt);

    grasp = 1;			    // grasp
    if (real_robot) {
        graspit();
    }
    else {
        sendJointState(TH0);
    }
    
    for (int i = 0; i < 50; i++) {
        loop_rate.sleep();
    }
    
    target << 0, -0.4, 0.6;			    // middle set point 
    
    invDiffKinematicControlSimComplete(target, pose.orientation, dt);
    
    switch (class_id)			    // go to the desired position depending on the class of the block
        {
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
        
    invDiffKinematicControlSimComplete(target, pose.orientation, dt);

    grasp = 0;			    // ungrasp
    
    if (real_robot) {
        graspit();
    }
    else {
        sendJointState(TH0);
    }
    
    for (int i = 0; i < 50; i++) {
        loop_rate.sleep();
    }
    
    target(2) = 0.65;			// lift a little bit
    
    invDiffKinematicControlSimComplete(target, pose.orientation, dt);
    sendJointState(TH0);
    
    target << 0, -0.4, 0.6;		// go to the middle point
    
    invDiffKinematicControlSimComplete(target, pose.orientation, dt);
    
    startingPosition();		// go to the starting position
    ack();
}

void startingPosition() {

    float dt; // time step
    dt = 0.001;
    Vector3f target;
    target << -.4, -.4, .6;
    invDiffKinematicControlSimComplete(target, pose.orientation, dt);
}

void ack() {

    ros::Rate loop_rate(LOOP_RATE);
    std_msgs::Int32 ack;
    ack.data = 1;
    
    for (int i = 0; i < 40; i++) { // wait a little bit before sending the ack to the taskManager (not stress too much the robot)
        loop_rate.sleep();
    }
    
    ack_pos.publish(ack);
}

void graspit()  // This function is used to map the gripper joints to the real robot
{
    ros_impedance_controller::generic_float gripper_diameter;
    if (grasp) {
        gripper_diameter.request.data = 60;
        client.call(gripper_diameter);
    }
    else {
        gripper_diameter.request.data = 100;
        client.call(gripper_diameter);
    }
}
