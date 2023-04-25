cmake_minimum_required(VERSION 3.0.2)
project(vision)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
)

catkin_package()

include_directories(include ${catkin_INCLUDE_DIRS})

catkin_install_python(PROGRAMS
  scripts/vision.py
  scripts/LegoDetect.py
  scripts/RegionOfInterest.py
  DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)
