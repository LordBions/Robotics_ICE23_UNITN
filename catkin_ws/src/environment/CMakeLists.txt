cmake_minimum_required(VERSION 3.0.2)
project(environment)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
)

## Generate messages in the 'msg' folder
# add_message_files(
#   FILES
#   Message1.msg
#   Message2.msg
# )

catkin_package()

include_directories(include ${catkin_INCLUDE_DIRS} )

add_executable(spawnLego src/spawnLego.cpp)
target_link_libraries(spawnLego ${catkin_LIBRARIES})

install(TARGETS spawnLego
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

# add_executable(imageCapture src/imageCapture.cpp)
# target_link_libraries(imageCapture ${catkin_LIBRARIES})

# install(TARGETS imageCapture
#  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
#  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
#  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
#)
