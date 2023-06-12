/**
 * @file kinetics.h
 * @authors Filippo Conti, Mattia Meneghin e Nicola Gianuzzi
 * @brief Provides some useful tools for planner and movement
 * @version 0.1
 * @copyright Copyright (c) 2023
 */

#ifndef KINETICS_H
#define KINETICS_H

#include <iostream>
#include <cmath>

/// Library that provides functionality for working with complex number in C++
#include <complex>

// Dense module of the Eigen library
// includes the necessary classes and functions for dense matrix operations
// provides a wide range of functionalities, including matrix arithmetic operations
#include <Eigen/Dense>

using namespace std;

/**
 * @brief This is the vector having the norm = 0
 */
#define null_vector 0, 0, 0 // this is the vector having the norm = 0

/**
 * @brief Describes the orientations of an object in the workspace
 * @param position      pose of object
 * @param orientation   orientation of object
 * @note mainly used by movement module
 */
struct objectPositionOrientation {
        Eigen::Vector3f position;
        Eigen::Vector3f orientation;
};

/**
 * @brief Describes the end effector
 * @param posit     position of end effector
 * @param orient    orientation of end effector
 */
struct end_effector {
    Eigen::Vector3f posit;
    Eigen::Matrix3f orient;
};

/**
 * @brief trasforms Euler angles in a 3x3 matrix
 * 
 * @param eu_angles     Euler angles
 * @return Eigen::Matrix3f 
 */
Eigen::Matrix3f orient2matrix(Eigen::Vector3f eu_angles) {

    Eigen::Matrix3f resMatrix;
    resMatrix = Eigen::AngleAxisf(eu_angles(0), Eigen::Vector3f::UnitZ()) * Eigen::AngleAxisf(eu_angles(1), Eigen::Vector3f::UnitY()) * Eigen::AngleAxisf(eu_angles(2), Eigen::Vector3f::UnitX());
    return resMatrix;
}

// It calculates the orientation error between two given orientation matrices
/**
 * @brief Calculates the orientation error between two given orientation matrices
 * 
 * @param curr_orientation      current orientation
 * @param final_orientation     desired orientation
 * @return Eigen::Vector3f 
 */
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

/**
 * @brief Calculates the jacobian Matrix related to the change of the reference system
 * 
 * @param jo_ang 
 * @return Eigen::MatrixXf 
 */
Eigen::MatrixXf jacobMatrix(Eigen::VectorXf jo_ang) {

    Eigen::VectorXf v_1(6);
    v_1 << 0, -0.425, -0.3922, 0, 0, 0;

    Eigen::VectorXf v_2(6);
    v_2 << 0.1625, 0, 0, 0.1333, 0.0997, 0.0996 + 0.14;

    Eigen::MatrixXf jac_mtx_1(6, 1);
    jac_mtx_1 <<    v_2(4) * (cos(jo_ang(0)) * cos(jo_ang(4)) + cos(jo_ang(1) + jo_ang(2) + jo_ang(3)) * sin(jo_ang(0)) * sin(jo_ang(4))) + v_2(2) * cos(jo_ang(0)) + v_2(3) * cos(jo_ang(0)) - v_1(2) * cos(jo_ang(1) + jo_ang(2)) * sin(jo_ang(0)) - v_1(1) * cos(jo_ang(1)) * sin(jo_ang(0)) - v_2(4) * sin(jo_ang(1) + jo_ang(2) + jo_ang(3)) * sin(jo_ang(0)),
                    v_2(4) * (cos(jo_ang(4)) * sin(jo_ang(0)) - cos(jo_ang(1) + jo_ang(2) + jo_ang(3)) * cos(jo_ang(0)) * sin(jo_ang(4))) + v_2(2) * sin(jo_ang(0)) + v_2(3) * sin(jo_ang(0)) + v_1(2) * cos(jo_ang(1) + jo_ang(2)) * cos(jo_ang(0)) + v_1(1) * cos(jo_ang(0)) * cos(jo_ang(1)) + v_2(4) * sin(jo_ang(1) + jo_ang(2) + jo_ang(3)) * cos(jo_ang(0)),
                    0,
                    0,
                    0,
                    1;
    
    Eigen::MatrixXf jac_mtx_2(6, 1);
    jac_mtx_2 <<    -cos(jo_ang(0)) * (v_1(2) * sin(jo_ang(1) + jo_ang(2)) + v_1(1) * sin(jo_ang(1)) + v_2(4) * (sin(jo_ang(1) + jo_ang(2)) * sin(jo_ang(3)) - cos(jo_ang(1) + jo_ang(2)) * cos(jo_ang(3))) - v_2(4) * sin(jo_ang(4)) * (cos(jo_ang(1) + jo_ang(2)) * sin(jo_ang(3)) + sin(jo_ang(1) + jo_ang(2)) * cos(jo_ang(3)))),
                    -sin(jo_ang(0)) * (v_1(2) * sin(jo_ang(1) + jo_ang(2)) + v_1(1) * sin(jo_ang(1)) + v_2(4) * (sin(jo_ang(1) + jo_ang(2)) * sin(jo_ang(3)) - cos(jo_ang(1) + jo_ang(2)) * cos(jo_ang(3))) - v_2(4) * sin(jo_ang(4)) * (cos(jo_ang(1) + jo_ang(2)) * sin(jo_ang(3)) + sin(jo_ang(1) + jo_ang(2)) * cos(jo_ang(3)))),
                    v_1(2) * cos(jo_ang(1) + jo_ang(2)) - (v_2(4) * sin(jo_ang(1) + jo_ang(2) + jo_ang(3) + jo_ang(4))) / 2 + v_1(1) * cos(jo_ang(1)) + (v_2(4) * sin(jo_ang(1) + jo_ang(2) + jo_ang(3) - jo_ang(4))) / 2 + v_2(4) * sin(jo_ang(1) + jo_ang(2) + jo_ang(3)),
                    sin(jo_ang(0)),
                    -cos(jo_ang(0)),
                    0;
    
    Eigen::MatrixXf jac_mtx_3(6, 1);
    jac_mtx_3 <<    cos(jo_ang(0)) * (v_2(4) * cos(jo_ang(1) + jo_ang(2) + jo_ang(3)) - v_1(2) * sin(jo_ang(1) + jo_ang(2)) + v_2(4) * sin(jo_ang(1) + jo_ang(2) + jo_ang(3)) * sin(jo_ang(4))),
                    sin(jo_ang(0)) * (v_2(4) * cos(jo_ang(1) + jo_ang(2) + jo_ang(3)) - v_1(2) * sin(jo_ang(1) + jo_ang(2)) + v_2(4) * sin(jo_ang(1) + jo_ang(2) + jo_ang(3)) * sin(jo_ang(4))),
                    v_1(2) * cos(jo_ang(1) + jo_ang(2)) - (v_2(4) * sin(jo_ang(1) + jo_ang(2) + jo_ang(3) + jo_ang(4))) / 2 + (v_2(4) * sin(jo_ang(1) + jo_ang(2) + jo_ang(3) - jo_ang(4))) / 2 + v_2(4) * sin(jo_ang(1) + jo_ang(2) + jo_ang(3)),
                    sin(jo_ang(0)),
                    -cos(jo_ang(0)),
                    0;
    
    Eigen::MatrixXf jac_mtx_4(6, 1);
    jac_mtx_4 <<    v_2(4) * cos(jo_ang(0)) * (cos(jo_ang(1) + jo_ang(2) + jo_ang(3)) + sin(jo_ang(1) + jo_ang(2) + jo_ang(3)) * sin(jo_ang(4))),
                    v_2(4) * sin(jo_ang(0)) * (cos(jo_ang(1) + jo_ang(2) + jo_ang(3)) + sin(jo_ang(1) + jo_ang(2) + jo_ang(3)) * sin(jo_ang(4))),
                    v_2(4) * (sin(jo_ang(1) + jo_ang(2) + jo_ang(3) - jo_ang(4)) / 2 + sin(jo_ang(1) + jo_ang(2) + jo_ang(3)) - sin(jo_ang(1) + jo_ang(2) + jo_ang(3) + jo_ang(4)) / 2),
                    sin(jo_ang(0)),
                    -cos(jo_ang(0)),
                    0;
    
    Eigen::MatrixXf jac_mtx_5(6, 1);
    jac_mtx_5 <<    -v_2(4) * sin(jo_ang(0)) * sin(jo_ang(4)) - v_2(4) * cos(jo_ang(1) + jo_ang(2) + jo_ang(3)) * cos(jo_ang(0)) * cos(jo_ang(4)),
                    v_2(4) * cos(jo_ang(0)) * sin(jo_ang(4)) - v_2(4) * cos(jo_ang(1) + jo_ang(2) + jo_ang(3)) * cos(jo_ang(4)) * sin(jo_ang(0)),
                    -v_2(4) * (sin(jo_ang(1) + jo_ang(2) + jo_ang(3) - jo_ang(4)) / 2 + sin(jo_ang(1) + jo_ang(2) + jo_ang(3) + jo_ang(4)) / 2),
                    sin(jo_ang(1) + jo_ang(2) + jo_ang(3)) * cos(jo_ang(0)),
                    sin(jo_ang(1) + jo_ang(2) + jo_ang(3)) * sin(jo_ang(0)),
                    -cos(jo_ang(1) + jo_ang(2) + jo_ang(3));
    
    Eigen::MatrixXf jac_mtx_6(6, 1);
    jac_mtx_6 <<    0,
                    0,
                    0,
                    cos(jo_ang(4)) * sin(jo_ang(0)) - cos(jo_ang(1) + jo_ang(2) + jo_ang(3)) * cos(jo_ang(0)) * sin(jo_ang(4)),
                    -cos(jo_ang(0)) * cos(jo_ang(4)) - cos(jo_ang(1) + jo_ang(2) + jo_ang(3)) * sin(jo_ang(0)) * sin(jo_ang(4)),
                    -sin(jo_ang(1) + jo_ang(2) + jo_ang(3)) * sin(jo_ang(4));
    
    Eigen::MatrixXf jacob_mtx(6, 6);
    jacob_mtx.setZero();
    jacob_mtx << jac_mtx_1, jac_mtx_2, jac_mtx_3, jac_mtx_4, jac_mtx_5, jac_mtx_6;
    return jacob_mtx;
}

/**
 * @brief Calculates the transformation matrix for the joint 1 given an input angle between joint 0 and 1
 * 
 * @param j1_angle      joint 1 angle
 * @return Eigen::Matrix4f 
 */
Eigen::Matrix4f joint1Transf(float j1_angle) {

    Eigen::VectorXf j1_1(6);
    j1_1 << 0, -0.425, -0.3922, 0, 0, 0;

    Eigen::VectorXf j1_2(6);
    j1_2 << 0.1625, 0, 0, 0.1333, 0.0997, 0.0996 + 0.14;
    
    Eigen::Matrix4f j1_matrix;
    j1_matrix << cos(j1_angle), -sin(j1_angle), 0, 0, sin(j1_angle), cos(j1_angle), 0, 0, 0, 0, 1, j1_2(0), 0, 0, 0, 1;
    return j1_matrix;
}

/**
 * @brief Calculates the transformation matrix for the joint 2 given an input angle between joint 1 and 2
 * 
 * @param j2_angle joint 2 angle
 * @return Eigen::Matrix4f 
 */
Eigen::Matrix4f joint2Transf(float j2_angle) {

    Eigen::VectorXf j2_1(6);
    j2_1 << 0, -0.425, -0.3922, 0, 0, 0;

    Eigen::VectorXf j2_2(6);
    j2_2 << 0.1625, 0, 0, 0.1333, 0.0997, 0.0996 + 0.14;

    Eigen::Matrix4f j2_matrix;
    j2_matrix << cos(j2_angle), -sin(j2_angle), 0, 0, 0, 0, -1, 0, sin(j2_angle), cos(j2_angle), 0, 0, 0, 0, 0, 1;
    return j2_matrix;
}

/**
 * @brief Calculates the transformation matrix for the joint 3 given an input angle between joint 2 and 3
 * 
 * @param j3_angle      joint 3 angle
 * @return Eigen::Matrix4f 
 */
Eigen::Matrix4f joint3Transf(float j3_angle) {

    Eigen::VectorXf j3_1(6);
    j3_1 << 0, -0.425, -0.3922, 0, 0, 0;

    Eigen::VectorXf j3_2(6);
    j3_2 << 0.1625, 0, 0, 0.1333, 0.0997, 0.0996 + 0.14;

    Eigen::Matrix4f j3_matrix;
    j3_matrix << cos(j3_angle), -sin(j3_angle), 0, j3_1(1), sin(j3_angle), cos(j3_angle), 0, 0, 0, 0, 1, j3_2(2), 0, 0, 0, 1;
    return j3_matrix;
}

/**
 * @brief Calculates the transformation matrix for the joint 4 given an input angle between joint 3 and 4
 * 
 * @param j4_angle joint 4 angle
 * @return Eigen::Matrix4f 
 */
Eigen::Matrix4f joint4Transf(float j4_angle) {

    Eigen::VectorXf j4_1(6);
    j4_1 << 0, -0.425, -0.3922, 0, 0, 0;

    Eigen::VectorXf j4_2(6);
    j4_2 << 0.1625, 0, 0, 0.1333, 0.0997, 0.0996 + 0.14;

    Eigen::Matrix4f j4_matrix;
    j4_matrix << cos(j4_angle), -sin(j4_angle), 0, j4_1(2), sin(j4_angle), cos(j4_angle), 0, 0, 0, 0, 1, j4_2(3), 0, 0, 0, 1;
    return j4_matrix;
}

/**
 * @brief Calculates the transformation matrix for the joint 5 given an input angle between joint 4 and 5
 * 
 * @param j5_angle      joint 5 angle
 * @return Eigen::Matrix4f 
 */
Eigen::Matrix4f joint5Transf(float j5_angle) {

    Eigen::VectorXf j5_1(6);
    j5_1 << 0, -0.425, -0.3922, 0, 0, 0;

    Eigen::VectorXf j5_2(6);
    j5_2 << 0.1625, 0, 0, 0.1333, 0.0997, 0.0996 + 0.14;

    Eigen::Matrix4f j5_matrix;
    j5_matrix << cos(j5_angle), -sin(j5_angle), 0, 0, 0, 0, -1, -j5_2(4), sin(j5_angle), cos(j5_angle), 0, 0, 0, 0, 0, 1;
    return j5_matrix;
}

/**
 * @brief Calculates the transformation matrix for the joint 6 given an input angle between joint 5 and 6
 * 
 * @param j6_angle joint 6 angle
 * @return Eigen::Matrix4f 
 */
Eigen::Matrix4f joint6Transf(float j6_angle) {

    Eigen::VectorXf j6_1(6);
    j6_1 << 0, -0.425, -0.3922, 0, 0, 0;

    Eigen::VectorXf j6_2(6);
    j6_2 << 0.1625, 0, 0, 0.1333, 0.0997, 0.0996 + 0.14;

    Eigen::Matrix4f j6_matrix;
    j6_matrix << cos(j6_angle), -sin(j6_angle), 0, 0, 0, 0, 1, j6_2(5), -sin(j6_angle), -cos(j6_angle), 0, 0, 0, 0, 0, 1;
    return j6_matrix;
}

/**
 * @brief Calculates the position and orientation of the end effector
 * 
 * @param j_angles joint angles
 * @return end_effector 
 */
end_effector directKinematic(Eigen::VectorXf j_angles) {

    Eigen::Matrix4f temp_mtx;
    temp_mtx = joint1Transf(j_angles(0)) * joint2Transf(j_angles(1)) * joint3Transf(j_angles(2)) * joint4Transf(j_angles(3)) * joint5Transf(j_angles(4)) * joint6Transf(j_angles(5));

    end_effector retMatrix;
    retMatrix.orient = temp_mtx.block(0, 0, 3, 3);
    retMatrix.posit = temp_mtx.block(0, 3, 3, 1);
    return retMatrix;
}

// Find the joint motion as a function of the “desired” end-effector motion and configuration
/**
 * @brief Finds the joint motion as a function of the “desired” end-effector motion and configuration
 * 
 * @param arm is the desired end effector
 * @return Eigen::MatrixXf 
 */
Eigen::MatrixXf inverseKinematic(end_effector &arm) {

    Eigen::VectorXf v_1d(6);
    v_1d << 0, -0.425, -0.3922, 0, 0, 0;

    Eigen::VectorXf v_2d(6);
    v_2d << 0.1625, 0, 0, 0.1333, 0.0997, 0.0996 + 0.14;

    Eigen::Matrix4f temp_mtx;
    temp_mtx.setZero();
    temp_mtx.block(0, 3, 3, 1) = arm.posit;
    temp_mtx.block(0, 0, 3, 3) = arm.orient;
    temp_mtx(3, 3) = 1;

    // finding th1

    Eigen::Vector4f j1_v;
    j1_v = temp_mtx * Eigen::Vector4f(0, 0, -v_2d(5), 1);
    float jo1_1 = real(atan2(j1_v(1), j1_v(0)) + acos(v_2d(3) / hypot(j1_v(1), j1_v(0)))) + M_PI / 2;
    float jo1_2 = real(atan2(j1_v(1), j1_v(0)) - acos(v_2d(3) / hypot(j1_v(1), j1_v(0)))) + M_PI / 2;

    // finding th5

    float jo5_1 = +real(acos((arm.posit(0) * sin(jo1_1) - arm.posit(1) * cos(jo1_1) - v_2d(3)) / v_2d(5)));
    float jo5_2 = -real(acos((arm.posit(0) * sin(jo1_1) - arm.posit(1) * cos(jo1_1) - v_2d(3)) / v_2d(5)));
    float jo5_3 = +real(acos((arm.posit(0) * sin(jo1_2) - arm.posit(1) * cos(jo1_2) - v_2d(3)) / v_2d(5)));
    float jo5_4 = -real(acos((arm.posit(0) * sin(jo1_2) - arm.posit(1) * cos(jo1_2) - v_2d(3)) / v_2d(5)));

    // finding th6

    Eigen::Matrix4f inv_mtx;
    inv_mtx = temp_mtx.inverse();

    Eigen::Vector3f x_vect;
    x_vect = inv_mtx.block(0, 0, 3, 1);

    Eigen::Vector3f y_vect;
    y_vect = inv_mtx.block(0, 1, 3, 1);

    float jo6_1 = real(atan2(((-x_vect(1) * sin(jo1_1) + y_vect(1) * cos(jo1_1))) / sin(jo5_1), ((x_vect(0) * sin(jo1_1) - y_vect(0) * cos(jo1_1))) / sin(jo5_1)));
    float jo6_2 = real(atan2(((-x_vect(1) * sin(jo1_1) + y_vect(1) * cos(jo1_1))) / sin(jo5_2), ((x_vect(0) * sin(jo1_1) - y_vect(0) * cos(jo1_1))) / sin(jo5_2)));
    float jo6_3 = real(atan2(((-x_vect(1) * sin(jo1_2) + y_vect(1) * cos(jo1_2))) / sin(jo5_3), ((x_vect(0) * sin(jo1_2) - y_vect(0) * cos(jo1_2))) / sin(jo5_3)));
    float jo6_4 = real(atan2(((-x_vect(1) * sin(jo1_2) + y_vect(1) * cos(jo1_2))) / sin(jo5_4), ((x_vect(0) * sin(jo1_2) - y_vect(0) * cos(jo1_2))) / sin(jo5_4)));

    Eigen::Matrix4f transf_mtx;
    transf_mtx = joint1Transf(jo1_1).inverse() * temp_mtx * joint6Transf(jo6_1).inverse() * joint5Transf(jo5_1).inverse();

    Eigen::Vector3f v4_1;
    v4_1 = transf_mtx.block(0, 3, 3, 1);

    float f4_1;
    f4_1 = hypot(v4_1(0), v4_1(2));

    transf_mtx = joint1Transf(jo1_1).inverse() * temp_mtx * joint6Transf(jo6_2).inverse() * joint5Transf(jo5_2).inverse();

    Eigen::Vector3f v4_2;    
    v4_2 = transf_mtx.block(0, 3, 3, 1);

    float f4_2;
    f4_2 = hypot(v4_2(0), v4_2(2));

    transf_mtx = joint1Transf(jo1_2).inverse() * temp_mtx * joint6Transf(jo6_3).inverse() * joint5Transf(jo5_3).inverse();

    Eigen::Vector3f v4_3;
    v4_3 = transf_mtx.block(0, 3, 3, 1);

    float f4_3;
    f4_3 = hypot(v4_3(0), v4_3(2));

    transf_mtx = joint1Transf(jo1_2).inverse() * temp_mtx * joint6Transf(jo6_4).inverse() * joint5Transf(jo5_4).inverse();

    Eigen::Vector3f v4_4;
    v4_4 = transf_mtx.block(0, 3, 3, 1);

    float f4_4;
    f4_4 = hypot(v4_4(0), v4_4(2));

    // find th3

    float jo3_1;
    if ((pow(f4_1, 2) - pow(v_1d(1), 2) - pow(v_1d(2), 2)) / (2 * v_1d(1) * v_1d(2)) > 1) { jo3_1 = 0; }
    else if ((pow(f4_1, 2) - pow(v_1d(1), 2) - pow(v_1d(2), 2)) / (2 * v_1d(1) * v_1d(2)) < -1) { jo3_1 = M_PI; }
    else { jo3_1 = acos((pow(f4_1, 2) - pow(v_1d(1), 2) - pow(v_1d(2), 2)) / (2 * v_1d(1) * v_1d(2))); }
    float jo3_5 = -jo3_1;

    float jo3_2;
    if ((pow(f4_2, 2) - pow(v_1d(1), 2) - pow(v_1d(2), 2)) / (2 * v_1d(1) * v_1d(2)) > 1) { jo3_2 = 0; }
    else if ((pow(f4_2, 2) - pow(v_1d(1), 2) - pow(v_1d(2), 2)) / (2 * v_1d(1) * v_1d(2)) < -1) { jo3_2 = M_PI; }
    else { jo3_2 = acos((pow(f4_2, 2) - pow(v_1d(1), 2) - pow(v_1d(2), 2)) / (2 * v_1d(1) * v_1d(2))); }
    float jo3_6 = -jo3_2;    

    float jo3_3;
    if ((pow(f4_3, 2) - pow(v_1d(1), 2) - pow(v_1d(2), 2)) / (2 * v_1d(1) * v_1d(2)) > 1) { jo3_3 = 0; }
    else if ((pow(f4_3, 2) - pow(v_1d(1), 2) - pow(v_1d(2), 2)) / (2 * v_1d(1) * v_1d(2)) < -1) { jo3_3 = M_PI; }
    else { jo3_3 = acos((pow(f4_3, 2) - pow(v_1d(1), 2) - pow(v_1d(2), 2)) / (2 * v_1d(1) * v_1d(2))); }
    float jo3_7 = -jo3_3;

    float jo3_4;
    if ((pow(f4_4, 2) - pow(v_1d(1), 2) - pow(v_1d(2), 2)) / (2 * v_1d(1) * v_1d(2)) > 1) { jo3_4 = 0; }
    else if ((pow(f4_4, 2) - pow(v_1d(1), 2) - pow(v_1d(2), 2)) / (2 * v_1d(1) * v_1d(2)) < -1) { jo3_4 = M_PI; }
    else { jo3_4 = acos((pow(f4_4, 2) - pow(v_1d(1), 2) - pow(v_1d(2), 2)) / (2 * v_1d(1) * v_1d(2))); }
    float jo3_8 = -jo3_4;

    // find th2

    float jo2_1 = atan2(-v4_1(2), -v4_1(0)) - asin((-v_1d(2) * sin(jo3_1)) / f4_1);
    float jo2_2 = atan2(-v4_2(2), -v4_2(0)) - asin((-v_1d(2) * sin(jo3_2)) / f4_2);
    float jo2_3 = atan2(-v4_3(2), -v4_3(0)) - asin((-v_1d(2) * sin(jo3_3)) / f4_3);
    float jo2_4 = atan2(-v4_4(2), -v4_4(0)) - asin((-v_1d(2) * sin(jo3_4)) / f4_4);
    float jo2_5 = atan2(-v4_1(2), -v4_1(0)) - asin((v_1d(2) * sin(jo3_1)) / f4_1);
    float jo2_6 = atan2(-v4_2(2), -v4_2(0)) - asin((v_1d(2) * sin(jo3_2)) / f4_2);
    float jo2_7 = atan2(-v4_3(2), -v4_3(0)) - asin((v_1d(2) * sin(jo3_3)) / f4_3);
    float jo2_8 = atan2(-v4_4(2), -v4_4(0)) - asin((v_1d(2) * sin(jo3_4)) / f4_4);

    // find th4

    Eigen::Matrix4f j4_mtx;    
    j4_mtx = joint3Transf(jo3_1).inverse() * joint2Transf(jo2_1).inverse() * joint1Transf(jo1_1).inverse() * temp_mtx * joint6Transf(jo6_1).inverse() * joint5Transf(jo5_1).inverse();
    
    Eigen::Vector3f x_4v;
    x_4v = j4_mtx.block(0, 0, 3, 1);
    float jo4_1 = atan2(x_4v(1), x_4v(0));

    j4_mtx = joint3Transf(jo3_2).inverse() * joint2Transf(jo2_2).inverse() * joint1Transf(jo1_1).inverse() * temp_mtx * joint6Transf(jo6_2).inverse() * joint5Transf(jo5_2).inverse();
    x_4v = j4_mtx.block(0, 0, 3, 1);
    float jo4_2 = atan2(x_4v(1), x_4v(0));

    j4_mtx = joint3Transf(jo3_3).inverse() * joint2Transf(jo2_3).inverse() * joint1Transf(jo1_2).inverse() * temp_mtx * joint6Transf(jo6_3).inverse() * joint5Transf(jo5_3).inverse();
    x_4v = j4_mtx.block(0, 0, 3, 1);
    float jo4_3 = atan2(x_4v(1), x_4v(0));

    j4_mtx = joint3Transf(jo3_4).inverse() * joint2Transf(jo2_4).inverse() * joint1Transf(jo1_2).inverse() * temp_mtx * joint6Transf(jo6_4).inverse() * joint5Transf(jo5_4).inverse();
    x_4v = j4_mtx.block(0, 0, 3, 1);
    float jo4_4 = atan2(x_4v(1), x_4v(0));

    j4_mtx = joint3Transf(jo3_5).inverse() * joint2Transf(jo2_5).inverse() * joint1Transf(jo1_1).inverse() * temp_mtx * joint6Transf(jo6_1).inverse() * joint5Transf(jo5_1).inverse();
    x_4v = j4_mtx.block(0, 0, 3, 1);
    float jo4_5 = atan2(x_4v(1), x_4v(0));

    j4_mtx = joint3Transf(jo3_6).inverse() * joint2Transf(jo2_6).inverse() * joint1Transf(jo1_1).inverse() * temp_mtx * joint6Transf(jo6_2).inverse() * joint5Transf(jo5_2).inverse();
    x_4v = j4_mtx.block(0, 0, 3, 1);
    float jo4_6 = atan2(x_4v(1), x_4v(0));

    j4_mtx = joint3Transf(jo3_7).inverse() * joint2Transf(jo2_7).inverse() * joint1Transf(jo1_2).inverse() * temp_mtx * joint6Transf(jo6_3).inverse() * joint5Transf(jo5_3).inverse();
    x_4v = j4_mtx.block(0, 0, 3, 1);
    float jo4_7 = atan2(x_4v(1), x_4v(0));

    j4_mtx = joint3Transf(jo3_8).inverse() * joint2Transf(jo2_8).inverse() * joint1Transf(jo1_2).inverse() * temp_mtx * joint6Transf(jo6_4).inverse() * joint5Transf(jo5_4).inverse();
    x_4v = j4_mtx.block(0, 0, 3, 1);
    float jo4_8 = atan2(x_4v(1), x_4v(0));

    Eigen::MatrixXf result_mtx(8, 6);
    result_mtx <<   jo1_1, jo2_1, jo3_1, jo4_1, jo5_1, jo6_1, jo1_1, jo2_2, jo3_2, jo4_2, jo5_2, jo6_2, jo1_2, jo2_3, jo3_3, jo4_3, jo5_3, jo6_3, jo1_2, jo2_4, jo3_4, jo4_4, jo5_4, jo6_4,
                    jo1_1, jo2_5, jo3_5, jo4_5, jo5_1, jo6_1, jo1_1, jo2_6, jo3_6, jo4_6, jo5_2, jo6_2, jo1_2, jo2_7, jo3_7, jo4_7, jo5_3, jo6_3, jo1_2, jo2_8, jo3_8, jo4_8, jo5_4, jo6_4;
    return result_mtx;
}

#endif
