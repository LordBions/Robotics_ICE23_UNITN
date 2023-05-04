#!/bin/bash

# EXECUTE ONLY ONCE without starting SH

echo " "
echo "Starting the environment..."
gnome-terminal -- python3 $HOME/Robotics_ICE23_UNITN/catkin_ws/src/control/ur5_generic.py

echo " "
echo "When the environment is ready and homing complete, "
read -p "PRESS ANY KEY to continue or close terminal in case of faliure " answer

echo " "
read -p " Please insert the assignment to execute: " assignment
rosrun ros_impedance_controller spawnLego.py -a $assignment

echo " "
echo "Starting the Planner module..."
gnome-terminal -- rosrun motion planner
sleep 3

echo " "
echo "Starting the Moviment module..."
gnome-terminal -- rosrun motion moviment
sleep 3

echo " "
echo "Starting the Vision module..."
gnome-terminal -- rosrun vision vision.py
sleep 3

echo "ALL STARTED!"
echo " "
