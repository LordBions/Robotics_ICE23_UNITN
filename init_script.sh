#!/bin/bash

echo '\n'
echo ' INIZIALIZATION SCRIPT'
echo '\n'
echo '-----------------------------------------'
echo '\n'
echo 'the REPO directory must be saved in $HOME'
cd $home

echo 'insert the password to give all permissions to our repo'
echo '\n'
sudo chmod -R 755 ./Robotics_ICE23_UNITN
echo '\n'

echo 'compiling the catkin packets'
cd ./Robotics_ICE23_UNITN/catkin_ws
catkin_make
echo '\n'

echo 'settng the source'
devel/setup.bash
echo '\n'

echo 'starting up ros core in other terminal'
gnome-terminal -- roscore
echo '\n'

echo 'wait the roscore starts for a minimum of seconds'
sleep 3s
echo '\n'

echo ' INIZIALIZATION COMPLETE'
echo '-----------------------------------------'
