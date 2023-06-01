# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "ros_impedance_controller: 5 messages, 4 services")

set(MSG_I_FLAGS "-Iros_impedance_controller:/home/utente/Robotics_ICE23_UNITN/catkin_ws/src/locosim/ros_impedance_controller/msg;-Igeometry_msgs:/opt/ros/noetic/share/geometry_msgs/cmake/../msg;-Istd_msgs:/opt/ros/noetic/share/std_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(geneus REQUIRED)
find_package(genlisp REQUIRED)
find_package(gennodejs REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(ros_impedance_controller_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/utente/Robotics_ICE23_UNITN/catkin_ws/src/locosim/ros_impedance_controller/msg/pid.msg" NAME_WE)
add_custom_target(_ros_impedance_controller_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "ros_impedance_controller" "/home/utente/Robotics_ICE23_UNITN/catkin_ws/src/locosim/ros_impedance_controller/msg/pid.msg" ""
)

get_filename_component(_filename "/home/utente/Robotics_ICE23_UNITN/catkin_ws/src/locosim/ros_impedance_controller/msg/BaseState.msg" NAME_WE)
add_custom_target(_ros_impedance_controller_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "ros_impedance_controller" "/home/utente/Robotics_ICE23_UNITN/catkin_ws/src/locosim/ros_impedance_controller/msg/BaseState.msg" "geometry_msgs/Point:geometry_msgs/Twist:geometry_msgs/Vector3:geometry_msgs/Pose:geometry_msgs/Quaternion:std_msgs/Header"
)

get_filename_component(_filename "/home/utente/Robotics_ICE23_UNITN/catkin_ws/src/locosim/ros_impedance_controller/msg/ContactsState.msg" NAME_WE)
add_custom_target(_ros_impedance_controller_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "ros_impedance_controller" "/home/utente/Robotics_ICE23_UNITN/catkin_ws/src/locosim/ros_impedance_controller/msg/ContactsState.msg" ""
)

get_filename_component(_filename "/home/utente/Robotics_ICE23_UNITN/catkin_ws/src/locosim/ros_impedance_controller/msg/Forces.msg" NAME_WE)
add_custom_target(_ros_impedance_controller_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "ros_impedance_controller" "/home/utente/Robotics_ICE23_UNITN/catkin_ws/src/locosim/ros_impedance_controller/msg/Forces.msg" "geometry_msgs/Point"
)

get_filename_component(_filename "/home/utente/Robotics_ICE23_UNITN/catkin_ws/src/locosim/ros_impedance_controller/msg/EffortPid.msg" NAME_WE)
add_custom_target(_ros_impedance_controller_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "ros_impedance_controller" "/home/utente/Robotics_ICE23_UNITN/catkin_ws/src/locosim/ros_impedance_controller/msg/EffortPid.msg" "std_msgs/Header"
)

get_filename_component(_filename "/home/utente/Robotics_ICE23_UNITN/catkin_ws/src/locosim/ros_impedance_controller/srv/set_pids.srv" NAME_WE)
add_custom_target(_ros_impedance_controller_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "ros_impedance_controller" "/home/utente/Robotics_ICE23_UNITN/catkin_ws/src/locosim/ros_impedance_controller/srv/set_pids.srv" "ros_impedance_controller/pid"
)

get_filename_component(_filename "/home/utente/Robotics_ICE23_UNITN/catkin_ws/src/locosim/ros_impedance_controller/srv/get_map.srv" NAME_WE)
add_custom_target(_ros_impedance_controller_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "ros_impedance_controller" "/home/utente/Robotics_ICE23_UNITN/catkin_ws/src/locosim/ros_impedance_controller/srv/get_map.srv" "geometry_msgs/Point"
)

get_filename_component(_filename "/home/utente/Robotics_ICE23_UNITN/catkin_ws/src/locosim/ros_impedance_controller/srv/get_effort_pid.srv" NAME_WE)
add_custom_target(_ros_impedance_controller_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "ros_impedance_controller" "/home/utente/Robotics_ICE23_UNITN/catkin_ws/src/locosim/ros_impedance_controller/srv/get_effort_pid.srv" ""
)

get_filename_component(_filename "/home/utente/Robotics_ICE23_UNITN/catkin_ws/src/locosim/ros_impedance_controller/srv/generic_float.srv" NAME_WE)
add_custom_target(_ros_impedance_controller_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "ros_impedance_controller" "/home/utente/Robotics_ICE23_UNITN/catkin_ws/src/locosim/ros_impedance_controller/srv/generic_float.srv" ""
)

#
#  langs = gencpp;geneus;genlisp;gennodejs;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(ros_impedance_controller
  "/home/utente/Robotics_ICE23_UNITN/catkin_ws/src/locosim/ros_impedance_controller/msg/pid.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/ros_impedance_controller
)
_generate_msg_cpp(ros_impedance_controller
  "/home/utente/Robotics_ICE23_UNITN/catkin_ws/src/locosim/ros_impedance_controller/msg/BaseState.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Twist.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Vector3.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/ros_impedance_controller
)
_generate_msg_cpp(ros_impedance_controller
  "/home/utente/Robotics_ICE23_UNITN/catkin_ws/src/locosim/ros_impedance_controller/msg/ContactsState.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/ros_impedance_controller
)
_generate_msg_cpp(ros_impedance_controller
  "/home/utente/Robotics_ICE23_UNITN/catkin_ws/src/locosim/ros_impedance_controller/msg/Forces.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/ros_impedance_controller
)
_generate_msg_cpp(ros_impedance_controller
  "/home/utente/Robotics_ICE23_UNITN/catkin_ws/src/locosim/ros_impedance_controller/msg/EffortPid.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/ros_impedance_controller
)

### Generating Services
_generate_srv_cpp(ros_impedance_controller
  "/home/utente/Robotics_ICE23_UNITN/catkin_ws/src/locosim/ros_impedance_controller/srv/set_pids.srv"
  "${MSG_I_FLAGS}"
  "/home/utente/Robotics_ICE23_UNITN/catkin_ws/src/locosim/ros_impedance_controller/msg/pid.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/ros_impedance_controller
)
_generate_srv_cpp(ros_impedance_controller
  "/home/utente/Robotics_ICE23_UNITN/catkin_ws/src/locosim/ros_impedance_controller/srv/get_map.srv"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/ros_impedance_controller
)
_generate_srv_cpp(ros_impedance_controller
  "/home/utente/Robotics_ICE23_UNITN/catkin_ws/src/locosim/ros_impedance_controller/srv/get_effort_pid.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/ros_impedance_controller
)
_generate_srv_cpp(ros_impedance_controller
  "/home/utente/Robotics_ICE23_UNITN/catkin_ws/src/locosim/ros_impedance_controller/srv/generic_float.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/ros_impedance_controller
)

### Generating Module File
_generate_module_cpp(ros_impedance_controller
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/ros_impedance_controller
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(ros_impedance_controller_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(ros_impedance_controller_generate_messages ros_impedance_controller_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/utente/Robotics_ICE23_UNITN/catkin_ws/src/locosim/ros_impedance_controller/msg/pid.msg" NAME_WE)
add_dependencies(ros_impedance_controller_generate_messages_cpp _ros_impedance_controller_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/utente/Robotics_ICE23_UNITN/catkin_ws/src/locosim/ros_impedance_controller/msg/BaseState.msg" NAME_WE)
add_dependencies(ros_impedance_controller_generate_messages_cpp _ros_impedance_controller_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/utente/Robotics_ICE23_UNITN/catkin_ws/src/locosim/ros_impedance_controller/msg/ContactsState.msg" NAME_WE)
add_dependencies(ros_impedance_controller_generate_messages_cpp _ros_impedance_controller_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/utente/Robotics_ICE23_UNITN/catkin_ws/src/locosim/ros_impedance_controller/msg/Forces.msg" NAME_WE)
add_dependencies(ros_impedance_controller_generate_messages_cpp _ros_impedance_controller_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/utente/Robotics_ICE23_UNITN/catkin_ws/src/locosim/ros_impedance_controller/msg/EffortPid.msg" NAME_WE)
add_dependencies(ros_impedance_controller_generate_messages_cpp _ros_impedance_controller_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/utente/Robotics_ICE23_UNITN/catkin_ws/src/locosim/ros_impedance_controller/srv/set_pids.srv" NAME_WE)
add_dependencies(ros_impedance_controller_generate_messages_cpp _ros_impedance_controller_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/utente/Robotics_ICE23_UNITN/catkin_ws/src/locosim/ros_impedance_controller/srv/get_map.srv" NAME_WE)
add_dependencies(ros_impedance_controller_generate_messages_cpp _ros_impedance_controller_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/utente/Robotics_ICE23_UNITN/catkin_ws/src/locosim/ros_impedance_controller/srv/get_effort_pid.srv" NAME_WE)
add_dependencies(ros_impedance_controller_generate_messages_cpp _ros_impedance_controller_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/utente/Robotics_ICE23_UNITN/catkin_ws/src/locosim/ros_impedance_controller/srv/generic_float.srv" NAME_WE)
add_dependencies(ros_impedance_controller_generate_messages_cpp _ros_impedance_controller_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(ros_impedance_controller_gencpp)
add_dependencies(ros_impedance_controller_gencpp ros_impedance_controller_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS ros_impedance_controller_generate_messages_cpp)

### Section generating for lang: geneus
### Generating Messages
_generate_msg_eus(ros_impedance_controller
  "/home/utente/Robotics_ICE23_UNITN/catkin_ws/src/locosim/ros_impedance_controller/msg/pid.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/ros_impedance_controller
)
_generate_msg_eus(ros_impedance_controller
  "/home/utente/Robotics_ICE23_UNITN/catkin_ws/src/locosim/ros_impedance_controller/msg/BaseState.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Twist.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Vector3.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/ros_impedance_controller
)
_generate_msg_eus(ros_impedance_controller
  "/home/utente/Robotics_ICE23_UNITN/catkin_ws/src/locosim/ros_impedance_controller/msg/ContactsState.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/ros_impedance_controller
)
_generate_msg_eus(ros_impedance_controller
  "/home/utente/Robotics_ICE23_UNITN/catkin_ws/src/locosim/ros_impedance_controller/msg/Forces.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/ros_impedance_controller
)
_generate_msg_eus(ros_impedance_controller
  "/home/utente/Robotics_ICE23_UNITN/catkin_ws/src/locosim/ros_impedance_controller/msg/EffortPid.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/ros_impedance_controller
)

### Generating Services
_generate_srv_eus(ros_impedance_controller
  "/home/utente/Robotics_ICE23_UNITN/catkin_ws/src/locosim/ros_impedance_controller/srv/set_pids.srv"
  "${MSG_I_FLAGS}"
  "/home/utente/Robotics_ICE23_UNITN/catkin_ws/src/locosim/ros_impedance_controller/msg/pid.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/ros_impedance_controller
)
_generate_srv_eus(ros_impedance_controller
  "/home/utente/Robotics_ICE23_UNITN/catkin_ws/src/locosim/ros_impedance_controller/srv/get_map.srv"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/ros_impedance_controller
)
_generate_srv_eus(ros_impedance_controller
  "/home/utente/Robotics_ICE23_UNITN/catkin_ws/src/locosim/ros_impedance_controller/srv/get_effort_pid.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/ros_impedance_controller
)
_generate_srv_eus(ros_impedance_controller
  "/home/utente/Robotics_ICE23_UNITN/catkin_ws/src/locosim/ros_impedance_controller/srv/generic_float.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/ros_impedance_controller
)

### Generating Module File
_generate_module_eus(ros_impedance_controller
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/ros_impedance_controller
  "${ALL_GEN_OUTPUT_FILES_eus}"
)

add_custom_target(ros_impedance_controller_generate_messages_eus
  DEPENDS ${ALL_GEN_OUTPUT_FILES_eus}
)
add_dependencies(ros_impedance_controller_generate_messages ros_impedance_controller_generate_messages_eus)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/utente/Robotics_ICE23_UNITN/catkin_ws/src/locosim/ros_impedance_controller/msg/pid.msg" NAME_WE)
add_dependencies(ros_impedance_controller_generate_messages_eus _ros_impedance_controller_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/utente/Robotics_ICE23_UNITN/catkin_ws/src/locosim/ros_impedance_controller/msg/BaseState.msg" NAME_WE)
add_dependencies(ros_impedance_controller_generate_messages_eus _ros_impedance_controller_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/utente/Robotics_ICE23_UNITN/catkin_ws/src/locosim/ros_impedance_controller/msg/ContactsState.msg" NAME_WE)
add_dependencies(ros_impedance_controller_generate_messages_eus _ros_impedance_controller_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/utente/Robotics_ICE23_UNITN/catkin_ws/src/locosim/ros_impedance_controller/msg/Forces.msg" NAME_WE)
add_dependencies(ros_impedance_controller_generate_messages_eus _ros_impedance_controller_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/utente/Robotics_ICE23_UNITN/catkin_ws/src/locosim/ros_impedance_controller/msg/EffortPid.msg" NAME_WE)
add_dependencies(ros_impedance_controller_generate_messages_eus _ros_impedance_controller_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/utente/Robotics_ICE23_UNITN/catkin_ws/src/locosim/ros_impedance_controller/srv/set_pids.srv" NAME_WE)
add_dependencies(ros_impedance_controller_generate_messages_eus _ros_impedance_controller_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/utente/Robotics_ICE23_UNITN/catkin_ws/src/locosim/ros_impedance_controller/srv/get_map.srv" NAME_WE)
add_dependencies(ros_impedance_controller_generate_messages_eus _ros_impedance_controller_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/utente/Robotics_ICE23_UNITN/catkin_ws/src/locosim/ros_impedance_controller/srv/get_effort_pid.srv" NAME_WE)
add_dependencies(ros_impedance_controller_generate_messages_eus _ros_impedance_controller_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/utente/Robotics_ICE23_UNITN/catkin_ws/src/locosim/ros_impedance_controller/srv/generic_float.srv" NAME_WE)
add_dependencies(ros_impedance_controller_generate_messages_eus _ros_impedance_controller_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(ros_impedance_controller_geneus)
add_dependencies(ros_impedance_controller_geneus ros_impedance_controller_generate_messages_eus)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS ros_impedance_controller_generate_messages_eus)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(ros_impedance_controller
  "/home/utente/Robotics_ICE23_UNITN/catkin_ws/src/locosim/ros_impedance_controller/msg/pid.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/ros_impedance_controller
)
_generate_msg_lisp(ros_impedance_controller
  "/home/utente/Robotics_ICE23_UNITN/catkin_ws/src/locosim/ros_impedance_controller/msg/BaseState.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Twist.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Vector3.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/ros_impedance_controller
)
_generate_msg_lisp(ros_impedance_controller
  "/home/utente/Robotics_ICE23_UNITN/catkin_ws/src/locosim/ros_impedance_controller/msg/ContactsState.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/ros_impedance_controller
)
_generate_msg_lisp(ros_impedance_controller
  "/home/utente/Robotics_ICE23_UNITN/catkin_ws/src/locosim/ros_impedance_controller/msg/Forces.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/ros_impedance_controller
)
_generate_msg_lisp(ros_impedance_controller
  "/home/utente/Robotics_ICE23_UNITN/catkin_ws/src/locosim/ros_impedance_controller/msg/EffortPid.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/ros_impedance_controller
)

### Generating Services
_generate_srv_lisp(ros_impedance_controller
  "/home/utente/Robotics_ICE23_UNITN/catkin_ws/src/locosim/ros_impedance_controller/srv/set_pids.srv"
  "${MSG_I_FLAGS}"
  "/home/utente/Robotics_ICE23_UNITN/catkin_ws/src/locosim/ros_impedance_controller/msg/pid.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/ros_impedance_controller
)
_generate_srv_lisp(ros_impedance_controller
  "/home/utente/Robotics_ICE23_UNITN/catkin_ws/src/locosim/ros_impedance_controller/srv/get_map.srv"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/ros_impedance_controller
)
_generate_srv_lisp(ros_impedance_controller
  "/home/utente/Robotics_ICE23_UNITN/catkin_ws/src/locosim/ros_impedance_controller/srv/get_effort_pid.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/ros_impedance_controller
)
_generate_srv_lisp(ros_impedance_controller
  "/home/utente/Robotics_ICE23_UNITN/catkin_ws/src/locosim/ros_impedance_controller/srv/generic_float.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/ros_impedance_controller
)

### Generating Module File
_generate_module_lisp(ros_impedance_controller
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/ros_impedance_controller
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(ros_impedance_controller_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(ros_impedance_controller_generate_messages ros_impedance_controller_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/utente/Robotics_ICE23_UNITN/catkin_ws/src/locosim/ros_impedance_controller/msg/pid.msg" NAME_WE)
add_dependencies(ros_impedance_controller_generate_messages_lisp _ros_impedance_controller_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/utente/Robotics_ICE23_UNITN/catkin_ws/src/locosim/ros_impedance_controller/msg/BaseState.msg" NAME_WE)
add_dependencies(ros_impedance_controller_generate_messages_lisp _ros_impedance_controller_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/utente/Robotics_ICE23_UNITN/catkin_ws/src/locosim/ros_impedance_controller/msg/ContactsState.msg" NAME_WE)
add_dependencies(ros_impedance_controller_generate_messages_lisp _ros_impedance_controller_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/utente/Robotics_ICE23_UNITN/catkin_ws/src/locosim/ros_impedance_controller/msg/Forces.msg" NAME_WE)
add_dependencies(ros_impedance_controller_generate_messages_lisp _ros_impedance_controller_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/utente/Robotics_ICE23_UNITN/catkin_ws/src/locosim/ros_impedance_controller/msg/EffortPid.msg" NAME_WE)
add_dependencies(ros_impedance_controller_generate_messages_lisp _ros_impedance_controller_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/utente/Robotics_ICE23_UNITN/catkin_ws/src/locosim/ros_impedance_controller/srv/set_pids.srv" NAME_WE)
add_dependencies(ros_impedance_controller_generate_messages_lisp _ros_impedance_controller_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/utente/Robotics_ICE23_UNITN/catkin_ws/src/locosim/ros_impedance_controller/srv/get_map.srv" NAME_WE)
add_dependencies(ros_impedance_controller_generate_messages_lisp _ros_impedance_controller_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/utente/Robotics_ICE23_UNITN/catkin_ws/src/locosim/ros_impedance_controller/srv/get_effort_pid.srv" NAME_WE)
add_dependencies(ros_impedance_controller_generate_messages_lisp _ros_impedance_controller_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/utente/Robotics_ICE23_UNITN/catkin_ws/src/locosim/ros_impedance_controller/srv/generic_float.srv" NAME_WE)
add_dependencies(ros_impedance_controller_generate_messages_lisp _ros_impedance_controller_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(ros_impedance_controller_genlisp)
add_dependencies(ros_impedance_controller_genlisp ros_impedance_controller_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS ros_impedance_controller_generate_messages_lisp)

### Section generating for lang: gennodejs
### Generating Messages
_generate_msg_nodejs(ros_impedance_controller
  "/home/utente/Robotics_ICE23_UNITN/catkin_ws/src/locosim/ros_impedance_controller/msg/pid.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/ros_impedance_controller
)
_generate_msg_nodejs(ros_impedance_controller
  "/home/utente/Robotics_ICE23_UNITN/catkin_ws/src/locosim/ros_impedance_controller/msg/BaseState.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Twist.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Vector3.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/ros_impedance_controller
)
_generate_msg_nodejs(ros_impedance_controller
  "/home/utente/Robotics_ICE23_UNITN/catkin_ws/src/locosim/ros_impedance_controller/msg/ContactsState.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/ros_impedance_controller
)
_generate_msg_nodejs(ros_impedance_controller
  "/home/utente/Robotics_ICE23_UNITN/catkin_ws/src/locosim/ros_impedance_controller/msg/Forces.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/ros_impedance_controller
)
_generate_msg_nodejs(ros_impedance_controller
  "/home/utente/Robotics_ICE23_UNITN/catkin_ws/src/locosim/ros_impedance_controller/msg/EffortPid.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/ros_impedance_controller
)

### Generating Services
_generate_srv_nodejs(ros_impedance_controller
  "/home/utente/Robotics_ICE23_UNITN/catkin_ws/src/locosim/ros_impedance_controller/srv/set_pids.srv"
  "${MSG_I_FLAGS}"
  "/home/utente/Robotics_ICE23_UNITN/catkin_ws/src/locosim/ros_impedance_controller/msg/pid.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/ros_impedance_controller
)
_generate_srv_nodejs(ros_impedance_controller
  "/home/utente/Robotics_ICE23_UNITN/catkin_ws/src/locosim/ros_impedance_controller/srv/get_map.srv"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/ros_impedance_controller
)
_generate_srv_nodejs(ros_impedance_controller
  "/home/utente/Robotics_ICE23_UNITN/catkin_ws/src/locosim/ros_impedance_controller/srv/get_effort_pid.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/ros_impedance_controller
)
_generate_srv_nodejs(ros_impedance_controller
  "/home/utente/Robotics_ICE23_UNITN/catkin_ws/src/locosim/ros_impedance_controller/srv/generic_float.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/ros_impedance_controller
)

### Generating Module File
_generate_module_nodejs(ros_impedance_controller
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/ros_impedance_controller
  "${ALL_GEN_OUTPUT_FILES_nodejs}"
)

add_custom_target(ros_impedance_controller_generate_messages_nodejs
  DEPENDS ${ALL_GEN_OUTPUT_FILES_nodejs}
)
add_dependencies(ros_impedance_controller_generate_messages ros_impedance_controller_generate_messages_nodejs)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/utente/Robotics_ICE23_UNITN/catkin_ws/src/locosim/ros_impedance_controller/msg/pid.msg" NAME_WE)
add_dependencies(ros_impedance_controller_generate_messages_nodejs _ros_impedance_controller_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/utente/Robotics_ICE23_UNITN/catkin_ws/src/locosim/ros_impedance_controller/msg/BaseState.msg" NAME_WE)
add_dependencies(ros_impedance_controller_generate_messages_nodejs _ros_impedance_controller_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/utente/Robotics_ICE23_UNITN/catkin_ws/src/locosim/ros_impedance_controller/msg/ContactsState.msg" NAME_WE)
add_dependencies(ros_impedance_controller_generate_messages_nodejs _ros_impedance_controller_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/utente/Robotics_ICE23_UNITN/catkin_ws/src/locosim/ros_impedance_controller/msg/Forces.msg" NAME_WE)
add_dependencies(ros_impedance_controller_generate_messages_nodejs _ros_impedance_controller_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/utente/Robotics_ICE23_UNITN/catkin_ws/src/locosim/ros_impedance_controller/msg/EffortPid.msg" NAME_WE)
add_dependencies(ros_impedance_controller_generate_messages_nodejs _ros_impedance_controller_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/utente/Robotics_ICE23_UNITN/catkin_ws/src/locosim/ros_impedance_controller/srv/set_pids.srv" NAME_WE)
add_dependencies(ros_impedance_controller_generate_messages_nodejs _ros_impedance_controller_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/utente/Robotics_ICE23_UNITN/catkin_ws/src/locosim/ros_impedance_controller/srv/get_map.srv" NAME_WE)
add_dependencies(ros_impedance_controller_generate_messages_nodejs _ros_impedance_controller_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/utente/Robotics_ICE23_UNITN/catkin_ws/src/locosim/ros_impedance_controller/srv/get_effort_pid.srv" NAME_WE)
add_dependencies(ros_impedance_controller_generate_messages_nodejs _ros_impedance_controller_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/utente/Robotics_ICE23_UNITN/catkin_ws/src/locosim/ros_impedance_controller/srv/generic_float.srv" NAME_WE)
add_dependencies(ros_impedance_controller_generate_messages_nodejs _ros_impedance_controller_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(ros_impedance_controller_gennodejs)
add_dependencies(ros_impedance_controller_gennodejs ros_impedance_controller_generate_messages_nodejs)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS ros_impedance_controller_generate_messages_nodejs)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(ros_impedance_controller
  "/home/utente/Robotics_ICE23_UNITN/catkin_ws/src/locosim/ros_impedance_controller/msg/pid.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/ros_impedance_controller
)
_generate_msg_py(ros_impedance_controller
  "/home/utente/Robotics_ICE23_UNITN/catkin_ws/src/locosim/ros_impedance_controller/msg/BaseState.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Twist.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Vector3.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/ros_impedance_controller
)
_generate_msg_py(ros_impedance_controller
  "/home/utente/Robotics_ICE23_UNITN/catkin_ws/src/locosim/ros_impedance_controller/msg/ContactsState.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/ros_impedance_controller
)
_generate_msg_py(ros_impedance_controller
  "/home/utente/Robotics_ICE23_UNITN/catkin_ws/src/locosim/ros_impedance_controller/msg/Forces.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/ros_impedance_controller
)
_generate_msg_py(ros_impedance_controller
  "/home/utente/Robotics_ICE23_UNITN/catkin_ws/src/locosim/ros_impedance_controller/msg/EffortPid.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/ros_impedance_controller
)

### Generating Services
_generate_srv_py(ros_impedance_controller
  "/home/utente/Robotics_ICE23_UNITN/catkin_ws/src/locosim/ros_impedance_controller/srv/set_pids.srv"
  "${MSG_I_FLAGS}"
  "/home/utente/Robotics_ICE23_UNITN/catkin_ws/src/locosim/ros_impedance_controller/msg/pid.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/ros_impedance_controller
)
_generate_srv_py(ros_impedance_controller
  "/home/utente/Robotics_ICE23_UNITN/catkin_ws/src/locosim/ros_impedance_controller/srv/get_map.srv"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/ros_impedance_controller
)
_generate_srv_py(ros_impedance_controller
  "/home/utente/Robotics_ICE23_UNITN/catkin_ws/src/locosim/ros_impedance_controller/srv/get_effort_pid.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/ros_impedance_controller
)
_generate_srv_py(ros_impedance_controller
  "/home/utente/Robotics_ICE23_UNITN/catkin_ws/src/locosim/ros_impedance_controller/srv/generic_float.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/ros_impedance_controller
)

### Generating Module File
_generate_module_py(ros_impedance_controller
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/ros_impedance_controller
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(ros_impedance_controller_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(ros_impedance_controller_generate_messages ros_impedance_controller_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/utente/Robotics_ICE23_UNITN/catkin_ws/src/locosim/ros_impedance_controller/msg/pid.msg" NAME_WE)
add_dependencies(ros_impedance_controller_generate_messages_py _ros_impedance_controller_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/utente/Robotics_ICE23_UNITN/catkin_ws/src/locosim/ros_impedance_controller/msg/BaseState.msg" NAME_WE)
add_dependencies(ros_impedance_controller_generate_messages_py _ros_impedance_controller_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/utente/Robotics_ICE23_UNITN/catkin_ws/src/locosim/ros_impedance_controller/msg/ContactsState.msg" NAME_WE)
add_dependencies(ros_impedance_controller_generate_messages_py _ros_impedance_controller_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/utente/Robotics_ICE23_UNITN/catkin_ws/src/locosim/ros_impedance_controller/msg/Forces.msg" NAME_WE)
add_dependencies(ros_impedance_controller_generate_messages_py _ros_impedance_controller_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/utente/Robotics_ICE23_UNITN/catkin_ws/src/locosim/ros_impedance_controller/msg/EffortPid.msg" NAME_WE)
add_dependencies(ros_impedance_controller_generate_messages_py _ros_impedance_controller_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/utente/Robotics_ICE23_UNITN/catkin_ws/src/locosim/ros_impedance_controller/srv/set_pids.srv" NAME_WE)
add_dependencies(ros_impedance_controller_generate_messages_py _ros_impedance_controller_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/utente/Robotics_ICE23_UNITN/catkin_ws/src/locosim/ros_impedance_controller/srv/get_map.srv" NAME_WE)
add_dependencies(ros_impedance_controller_generate_messages_py _ros_impedance_controller_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/utente/Robotics_ICE23_UNITN/catkin_ws/src/locosim/ros_impedance_controller/srv/get_effort_pid.srv" NAME_WE)
add_dependencies(ros_impedance_controller_generate_messages_py _ros_impedance_controller_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/utente/Robotics_ICE23_UNITN/catkin_ws/src/locosim/ros_impedance_controller/srv/generic_float.srv" NAME_WE)
add_dependencies(ros_impedance_controller_generate_messages_py _ros_impedance_controller_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(ros_impedance_controller_genpy)
add_dependencies(ros_impedance_controller_genpy ros_impedance_controller_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS ros_impedance_controller_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/ros_impedance_controller)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/ros_impedance_controller
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
if(TARGET geometry_msgs_generate_messages_cpp)
  add_dependencies(ros_impedance_controller_generate_messages_cpp geometry_msgs_generate_messages_cpp)
endif()

if(geneus_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/ros_impedance_controller)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/ros_impedance_controller
    DESTINATION ${geneus_INSTALL_DIR}
  )
endif()
if(TARGET geometry_msgs_generate_messages_eus)
  add_dependencies(ros_impedance_controller_generate_messages_eus geometry_msgs_generate_messages_eus)
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/ros_impedance_controller)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/ros_impedance_controller
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
if(TARGET geometry_msgs_generate_messages_lisp)
  add_dependencies(ros_impedance_controller_generate_messages_lisp geometry_msgs_generate_messages_lisp)
endif()

if(gennodejs_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/ros_impedance_controller)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/ros_impedance_controller
    DESTINATION ${gennodejs_INSTALL_DIR}
  )
endif()
if(TARGET geometry_msgs_generate_messages_nodejs)
  add_dependencies(ros_impedance_controller_generate_messages_nodejs geometry_msgs_generate_messages_nodejs)
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/ros_impedance_controller)
  install(CODE "execute_process(COMMAND \"/usr/bin/python3\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/ros_impedance_controller\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/ros_impedance_controller
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
if(TARGET geometry_msgs_generate_messages_py)
  add_dependencies(ros_impedance_controller_generate_messages_py geometry_msgs_generate_messages_py)
endif()
