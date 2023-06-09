# Install script for directory: /home/utente/Robotics_ICE23_UNITN/catkin_ws/src/locosim/robot_descriptions/climbingrobot_description

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/utente/Robotics_ICE23_UNITN/catkin_ws/install")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/objdump")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/home/utente/Robotics_ICE23_UNITN/catkin_ws/build/locosim/robot_descriptions/climbingrobot_description/catkin_generated/installspace/climbingrobot_description.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/climbingrobot_description/cmake" TYPE FILE FILES
    "/home/utente/Robotics_ICE23_UNITN/catkin_ws/build/locosim/robot_descriptions/climbingrobot_description/catkin_generated/installspace/climbingrobot_descriptionConfig.cmake"
    "/home/utente/Robotics_ICE23_UNITN/catkin_ws/build/locosim/robot_descriptions/climbingrobot_description/catkin_generated/installspace/climbingrobot_descriptionConfig-version.cmake"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/climbingrobot_description" TYPE FILE FILES "/home/utente/Robotics_ICE23_UNITN/catkin_ws/src/locosim/robot_descriptions/climbingrobot_description/package.xml")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/climbingrobot_description/config" TYPE DIRECTORY FILES "/home/utente/Robotics_ICE23_UNITN/catkin_ws/src/locosim/robot_descriptions/climbingrobot_description/config/" REGEX "/\\.svn$" EXCLUDE)
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/climbingrobot_description/gazebo" TYPE DIRECTORY FILES "/home/utente/Robotics_ICE23_UNITN/catkin_ws/src/locosim/robot_descriptions/climbingrobot_description/gazebo/" REGEX "/\\.svn$" EXCLUDE)
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/climbingrobot_description/launch" TYPE DIRECTORY FILES "/home/utente/Robotics_ICE23_UNITN/catkin_ws/src/locosim/robot_descriptions/climbingrobot_description/launch/" REGEX "/\\.svn$" EXCLUDE)
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/climbingrobot_description/rviz" TYPE DIRECTORY FILES "/home/utente/Robotics_ICE23_UNITN/catkin_ws/src/locosim/robot_descriptions/climbingrobot_description/rviz/" REGEX "/\\.svn$" EXCLUDE)
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/climbingrobot_description/meshes" TYPE DIRECTORY FILES "/home/utente/Robotics_ICE23_UNITN/catkin_ws/src/locosim/robot_descriptions/climbingrobot_description/meshes/" REGEX "/\\.svn$" EXCLUDE)
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/climbingrobot_description/urdf" TYPE DIRECTORY FILES "/home/utente/Robotics_ICE23_UNITN/catkin_ws/src/locosim/robot_descriptions/climbingrobot_description/urdf/" REGEX "/\\.svn$" EXCLUDE)
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/climbingrobot_description/rviz" TYPE DIRECTORY FILES "/home/utente/Robotics_ICE23_UNITN/catkin_ws/src/locosim/robot_descriptions/climbingrobot_description/rviz/" REGEX "/\\.svn$" EXCLUDE)
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/climbingrobot_description" TYPE PROGRAM FILES "/home/utente/Robotics_ICE23_UNITN/catkin_ws/build/locosim/robot_descriptions/climbingrobot_description/catkin_generated/installspace/go0")
endif()
