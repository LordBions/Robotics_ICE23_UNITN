#!/bin/bash

# EXECUTE ONLY ONCE without starting SH

echo "Starting the environment..."
gnome-terminal -- python3 $HOME/Robotics_ICE23_UNITN/catkin_ws/src/control/ur5_generic.py
read -p "When the environment is ready, press any key... " ready_answer

echo "Starting the Planner..."
gnome-terminal -- rosrun motion taskManager
sleep 5

echo "Starting the moviment..."
gnome-terminal -- rosrun motion motionPlanner
sleep 5

echo "Starting the vision..."
gnome-terminal -- python3 $HOME/Robotics_ICE23_UNITN/catkin_ws/src/vision/scripts/Vision.py
sleep 5

echo "ALL STARTED"
