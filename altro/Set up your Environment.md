This project will run only in Ubuntu 20.04 Focal Fossa
## Installing ROS
If you want to execute and work with our project, you need [ROS](http://wiki.ros.org/noetic/Installation/Ubuntu) installed in your computer:
1. You have to set up your computer in order to accept software from packages.ros.org
```
sudo sh -c 'echo "deb http://packages.ros.org/ros/ubuntu $(lsb_release -sc) main" > /etc/apt/sources.list.d/ros-latest.list'
```
2. Install curl (if you haven't already installed):
```
sudo apt install curl
```
3. Set up your keys:
```
curl -s https://raw.githubusercontent.com/ros/rosdistro/master/ros.asc | sudo apt-key add -
```
4. Run the system update command to update your existing repos and packages:
```
sudo apt-get update
```
5. Download ROS. Here there is the reccomended download:
```
sudo apt install ros-noetic-desktop-full
```
6. Once ROS is installed,  you must to set up ROS environment, typing:
```
echo "source /opt/ros/noetic/setup.bash" >> ~/.bashrc
source ~/.bashrc
```

## Installing python3
In order to install [python3](https://linuxize.com/post/how-to-install-pip-on-ubuntu-20.04/):
1. Run the system update command to update your existing repos and packages:
```
sudo apt update
```
2. Download python3
```
sudo apt install python3
```
3. check python3 version (it should be 3.8.10) using:
```
python3 --version
```

## Installing pip3
To install [pip3](https://linuxize.com/post/how-to-install-pip-on-ubuntu-20.04/):
1. Run the system update command to update your existing repos and packages:
```
sudo apt update
```
2. Download `pip3`
```
sudo apt install python3-pip
```
3. When the installation is complete, check `pip3` version (it should be *pip 20.0.2 from /usr/lib/python3/dist-packages/pip (python 3.8)*):
```
pip3 --version
```

## Installing Catkin
To install [catkin](https://catkin-tools.readthedocs.io/en/latest/installing.html):
1. you must have the ROS repositories which contain the `.deb` for `catkin_tools`:
```
sudo sh \
    -c 'echo "deb http://packages.ros.org/ros/ubuntu `lsb_release -sc` main" \
        > /etc/apt/sources.list.d/ros-latest.list'
```
2. Then type:
```
wget http://packages.ros.org/ros.key -O - | sudo apt-key add -
```
3. Run the system update command to update your existing repos and packages:
```
sudo apt-get update
```
4. Install `catkin_tools`:
```
sudo apt-get install python3-catkin-tools
```

If you want to set up your custom catkin workspace, [here](http://wiki.ros.org/catkin/Tutorials/create_a_workspace) you can find a guide provided by ROS that explain you how to do it.

## Installing Locosim
If you need some didactic framework to learn/test basic controllers schemes on quadruped robots that is continuosly update, we recommend to install Locosim.
You can find the Locosim guide [Here](https://github.com/mfocchi/locosim).
We can spoiler you that you need some prerequisites, such as `python3`, `pip3` and `ros-noetic` version, that you should already have.

## Install Robotics_ICE23_UNITN
*Robotics_ICE23_UNITN* is the project that we made for foundamentals of Robotics exam.
If you are interested in you can download and use it following this guide  from GitHub [here](https://github.com/LordBions/Robotics_ICE23_UNITN).