#!/bin/bash

# EXECUTE ONLY ONCE without starting SH

echo "Starting the environment..."
gnome-terminal -- python3 $HOME/Robotics_ICE23_UNITN/catkin_ws/src/control/ur5_generic.py
read -p "When the environment is ready and homing complete, press any key... " ready_answer

echo "Starting the Planner..."
gnome-terminal -- rosrun motion planner
sleep 3

echo "Starting the moviment..."
gnome-terminal -- rosrun motion moviment
sleep 3

echo "Starting the vision..."
gnome-terminal -- python3 $HOME/Robotics_ICE23_UNITN/catkin_ws/src/vision/scripts/vision.py
sleep 3

echo "ALL STARTED"
