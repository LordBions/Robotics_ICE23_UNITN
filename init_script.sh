#!/bin/bash
# setting up the catkin_ws directory
# the main directory must be saved in $HOME


cd $HOME/Robotics_ICE23_UNITN/catkin_ws
catkin_make
. $HOME/Robotics_ICE2023/catkin_ws/devel/setup.bash

