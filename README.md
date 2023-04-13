# Robotics_ICE23_UNITN
For university exam

## Set up
----------------------------
First of all, you need to set up your catkin_ws directory there are two possible methods:
1. Using 'init_script.sh'
2. Manually

### The init_scrit.sh
> *ATTENTION:* This script will run only if installed the main directory has been saved in $HOME 

1. Open your terminal and write:
```
cd $HOME/Robotics_ICE23_UNITN
```
2. Run the following command:
```
bash init_script.sh
``` 

### Setting up manually
If you are too pro and/or you don't want to save the directory in the $HOME folder, you can
set up the catkin_ws directory manually:
1. Open your terminal and type:
```
cd PATH/YOU/WANT/Robotics_ICE23_UNITN/catkin_ws
catkin_make
. PATH/YOU/WANT/Robotics_ICE2023/catkin_ws/devel/setup.bash
```

## Start the project
In you $HOME directory `git clone https://github.com/LordBions/Robotics_ICE23_UNITN.git`
In a terminal run `roscore` and leave it there

1. Open a new terminal
2. `cd ~/Robotics_ICE23_UNITN/catkin_ws && ls`  and should appear just src folder
3. `catkin_make`
4. `source devel/setup.bash`
> if there isn't **logs** folder you can create it manually with `mdkir -p ~/Robotics_ICE23_UNITN/catkin_ws/logs`
5. `cd ~/Robotics_ICE23_UNITN`
6. `roslaunch environment environment.launch` and should open a Gazebo instance
