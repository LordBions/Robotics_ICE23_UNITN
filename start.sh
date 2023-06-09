#!/bin/bash

trap 'printf "\n";stop;exit 1' 2

start(){
    planner
    movement
    vision
}

banner() {
    clear
    printf "     \n"
    printf "     \e[100m\e[1;77m:: Foundamentals of Robotics project          ::\e[0m\n"
    printf "     \e[100m\e[1;77m:: Authors:                                   ::\e[0m\n"
    printf "     \e[100m\e[1;77m::    - Conti Filippo                         ::\e[0m\n"
    printf "     \e[100m\e[1;77m::    - Gianuzzi Nicola                       ::\e[0m\n"
    printf "     \e[100m\e[1;77m::    - Meneghin Mattia                       ::\e[0m\n"
    printf "     \n"
}

assignment() {
    
    printf "Please insert the assignment number:                                          \n"
    printf "          \e[1;92m[\e[0m\e[1;77m1\e[0m\e[1;92m]\e[0m\e[1;91m Assignment 1\e[0m\n"                                
    printf "          \e[1;92m[\e[0m\e[1;77m2\e[0m\e[1;92m]\e[0m\e[1;91m Assignment 2\e[0m\n"
    printf "          \e[1;92m[\e[0m\e[1;77m3\e[0m\e[1;92m]\e[0m\e[1;91m Assignment 3\e[0m\n"
    printf "          \e[1;92m[\e[0m\e[1;77m4\e[0m\e[1;92m]\e[0m\e[1;91m Assignment 4\e[0m\n"                

    read -p "Choose an option: " option
    printf "Will be execute the assignment \e[1;92m[\e[0m\e[1;77m$option\e[0m\e[1;92m]\e[0m\n"

    if [[ $option == 1 ]]; then
        spawnLego 1
        start
    elif [[ $option == 2 ]]; then
        spawnLego 2
        start
    elif [[ $option == 3 ]]; then
        spawnLego 3
        start
    elif [[ $option == 4 ]]; then
        spawnLego 4
        start
    else
        printf "\e[1;93m [!] Invalid option!\e[0m\n"
        assignment
    fi
}


spawnLego(){
    assign=$1
    gnome-terminal --title="spawnLego" -- rosrun environment spawnLego -a$assign
    sleep 3
    printf "Starting the \e[1;93mSPAWNER\e[0m module\n"
}

environment(){
    printf "Starting the \e[1;93mENVIRONMENT\e[0m\n"
    gnome-terminal --title="environment" -- python3 $HOME/Robotics_ICE23_UNITN/catkin_ws/src/locosim/control/ur5_generic.py
    printf "\n"
}

next(){
    printf "     \e[101m\e[1;77m:: Note: Wait the end HOMING PROCEDURE        ::\e[0m\n"
    read -p "PRESS ANY KEY to continue or close terminal in case of faliure " answer
}

planner() {
    printf "Starting the \e[1;93mPLANNER\e[0m module\n"
    gnome-terminal --title="planner" -- rosrun motion planner
    sleep 3
}

movement() {
    printf "Starting the \e[1;93mMOVEMENT\e[0m module\n"
    gnome-terminal --title="movement" -- rosrun motion movement
    sleep 3
}


vision() {
    printf "Starting the \e[1;93mVISION\e[0m module\n"
    gnome-terminal --title="vision" -- rosrun vision vision.py
    sleep 3
}

selectModule(){
    printf "\nWhich module do you need?"
    printf "\n          \e[1;92m[\e[0m\e[1;77m0\e[0m\e[1;92m]\e[0m\e[1;91m EXIT \e[0m\n"
    printf "          \e[1;92m[\e[0m\e[1;77m1\e[0m\e[1;92m]\e[0m\e[1;91m planner\e[0m\n"                            
    printf "          \e[1;92m[\e[0m\e[1;77m2\e[0m\e[1;92m]\e[0m\e[1;91m movement\e[0m\n"
    printf "          \e[1;92m[\e[0m\e[1;77m3\e[0m\e[1;92m]\e[0m\e[1;91m vision\e[0m\n"

    read -p "Choose a module: " module
    printf "\n"

    if [[ $module == 0 ]]; then
        killNode
    elif [[ $module == 1 ]]; then
        planner
    elif [[ $module == 2 ]]; then
        movement
    elif [[ $module == 3 ]]; then
        vision
    else
        printf "\e[1;93m [!] Invalid option!\e[0m\n"
        selectModule
    fi
}

killNode(){
    rosnode kill --all
}

again() {
    printf "\nDo you need to re-call some modules? [\e[1;92mY\e[0m/\e[1;91mn\e[0m]\n"
    printf "If you type n all the ROS node will be killed\n"
    read -p "" _exit

    if [[ $_exit == Y ]]; then
        selectModule
    elif [[ $_exit == y ]]; then
        selectModule
    elif [[ $_exit == N ]]; then
        killNode
    elif [[ $_exit == n ]]; then
        killNode
    else
        printf "\e[1;93m [!] Invalid option!\e[0m\n"
        again
    fi
}

banner
environment
next
assignment

printf "\n\e[1;92mALL STARTED!\e[0m\n"
sleep 5

#End of the jobs

again