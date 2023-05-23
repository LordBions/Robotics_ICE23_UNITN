cmake_minimum_required(VERSION 3.0.2)
project(motion)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  message_generation
)

find_package(Eigen3 3.3 REQUIRED)

add_message_files(
  FILES
  legoTask.msg
  legoFound.msg
  eventResult.msg
)

generate_messages(
  DEPENDENCIES
  std_msgs
)

catkin_package()

include_directories(include ${catkin_INCLUDE_DIRS} ${EIGEN3_INCLUDE_DIRS})

add_executable(planner src/planner.cpp)
target_link_libraries(planner ${catkin_LIBRARIES})

install(TARGETS planner
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

add_executable(movement src/movement.cpp)
target_link_libraries(movement ${catkin_LIBRARIES})

install(TARGETS movement
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

add_executable(manualVision src/manualVision.cpp)
target_link_libraries(manualVision ${catkin_LIBRARIES})

install(TARGETS manualVision
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)
