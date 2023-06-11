#!/bin/bash

# EXECUTE ONLY ONCE without starting SH

echo " "
echo "Starting the environment..."
gnome-terminal -- python3 $HOME/Robotics_ICE23_UNITN/catkin_ws/src/locosim/control/ur5_generic.py

echo " "
echo "When the environment is ready and homing complete, "
read -p "PRESS ANY KEY to continue or close terminal in case of faliure " answer

echo " "
read -p " Please insert the assignment number: " assignment
gnome-terminal -- rosrun environment spawnLego -a$assignment

echo " "
echo "Starting the Vision module..."
gnome-terminal -- rosrun vision vision.py
sleep 3
