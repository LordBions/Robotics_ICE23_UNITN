#!/bin/bash

# EXECUTE without starting SH

# the main directory must be saved in $HOME
cd $HOME

# clone our repo
git clone https://github.com/LordBions/Robotics_ICE23_UNITN

# installare tutte le dipendency ed i requirements nostri
#............
#............
#............

# set the source
. $HOME/Robotics_ICE2023/catkin_ws/devel/setup.bash

# write the source into bash rc
echo "source $PWD/devel/setup.bash" >> $HOME/.bashrc

# setting up the catkin_ws directory
cd $HOME/Robotics_ICE23_UNITN/catkin_ws

# build the catkin packages
catkin_make

# run environment
roslaunch environment environment.launch
