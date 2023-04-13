#!/bin/bash

# EXECUTE without starting SH

# launch environment
gnome-terminal -- roslaunch environment environment.launch

echo ' Select the assignment number from 1 to 4:   '
read assignment_number
rosrun environment environment.py -a $assignment_number
