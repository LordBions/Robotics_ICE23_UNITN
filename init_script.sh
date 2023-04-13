#!/bin/bash

# EXECUTE ONLY ONCE without starting SH

# the main directory must be saved in $HOME
cd $HOME

# clone our repo ( uncomment when the repo is completed )
# git clone https://github.com/LordBions/Robotics_ICE23_UNITN

# installare tutte le dipendency ed i requirements nostri
# sudo apt install rospy
# sudo apt install quaternion
# sudo apt install zed camera
#............

# write the source into bash rc
# may be multiple lines if executed more than once
echo "source $HOME/Robotics_ICE23_UNITN/catkin_ws/devel/setup.bash" >> $HOME/.bashrc

# set the source
. $HOME/Robotics_ICE23_UNITN/catkin_ws/devel/setup.bash

# setting up the catkin_ws directory
cd $HOME/Robotics_ICE23_UNITN/catkin_ws

# build the catkin packages
catkin_make
