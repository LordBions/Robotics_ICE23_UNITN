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
If it *does not* work, type:
```
cd $HOME/Robotics_ICE23_UNITN; chmod +x ./init_script.sh; ./init_script.sh
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

