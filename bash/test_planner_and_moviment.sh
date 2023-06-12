#!/bin/bash

# EXECUTE ONLY ONCE without starting SH

echo " "
echo "Starting the ROS CORE..."
gnome-terminal -- roscore

echo " "
echo "When the ROS CORE is ready"
read -p "PRESS ANY KEY to continue or close terminal in case of faliure " answer

echo " "
echo "Starting the movement module..."
gnome-terminal -- rosrun motion movement
sleep 3

echo " "
echo "Starting the planner module..."
gnome-terminal -- rosrun motion planner -s
sleep 3
