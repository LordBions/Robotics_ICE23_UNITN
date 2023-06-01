# Install script for directory: /home/utente/Robotics_ICE23_UNITN/catkin_ws/src/locosim/ros_impedance_controller

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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ros_impedance_controller/msg" TYPE FILE FILES
    "/home/utente/Robotics_ICE23_UNITN/catkin_ws/src/locosim/ros_impedance_controller/msg/pid.msg"
    "/home/utente/Robotics_ICE23_UNITN/catkin_ws/src/locosim/ros_impedance_controller/msg/BaseState.msg"
    "/home/utente/Robotics_ICE23_UNITN/catkin_ws/src/locosim/ros_impedance_controller/msg/ContactsState.msg"
    "/home/utente/Robotics_ICE23_UNITN/catkin_ws/src/locosim/ros_impedance_controller/msg/Forces.msg"
    "/home/utente/Robotics_ICE23_UNITN/catkin_ws/src/locosim/ros_impedance_controller/msg/EffortPid.msg"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ros_impedance_controller/srv" TYPE FILE FILES
    "/home/utente/Robotics_ICE23_UNITN/catkin_ws/src/locosim/ros_impedance_controller/srv/set_pids.srv"
    "/home/utente/Robotics_ICE23_UNITN/catkin_ws/src/locosim/ros_impedance_controller/srv/get_map.srv"
    "/home/utente/Robotics_ICE23_UNITN/catkin_ws/src/locosim/ros_impedance_controller/srv/get_effort_pid.srv"
    "/home/utente/Robotics_ICE23_UNITN/catkin_ws/src/locosim/ros_impedance_controller/srv/generic_float.srv"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ros_impedance_controller/cmake" TYPE FILE FILES "/home/utente/Robotics_ICE23_UNITN/catkin_ws/build/locosim/ros_impedance_controller/catkin_generated/installspace/ros_impedance_controller-msg-paths.cmake")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE DIRECTORY FILES "/home/utente/Robotics_ICE23_UNITN/catkin_ws/devel/include/ros_impedance_controller")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/roseus/ros" TYPE DIRECTORY FILES "/home/utente/Robotics_ICE23_UNITN/catkin_ws/devel/share/roseus/ros/ros_impedance_controller")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/common-lisp/ros" TYPE DIRECTORY FILES "/home/utente/Robotics_ICE23_UNITN/catkin_ws/devel/share/common-lisp/ros/ros_impedance_controller")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/gennodejs/ros" TYPE DIRECTORY FILES "/home/utente/Robotics_ICE23_UNITN/catkin_ws/devel/share/gennodejs/ros/ros_impedance_controller")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  execute_process(COMMAND "/usr/bin/python3" -m compileall "/home/utente/Robotics_ICE23_UNITN/catkin_ws/devel/lib/python3/dist-packages/ros_impedance_controller")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/python3/dist-packages" TYPE DIRECTORY FILES "/home/utente/Robotics_ICE23_UNITN/catkin_ws/devel/lib/python3/dist-packages/ros_impedance_controller")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/home/utente/Robotics_ICE23_UNITN/catkin_ws/build/locosim/ros_impedance_controller/catkin_generated/installspace/ros_impedance_controller.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ros_impedance_controller/cmake" TYPE FILE FILES "/home/utente/Robotics_ICE23_UNITN/catkin_ws/build/locosim/ros_impedance_controller/catkin_generated/installspace/ros_impedance_controller-msg-extras.cmake")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ros_impedance_controller/cmake" TYPE FILE FILES
    "/home/utente/Robotics_ICE23_UNITN/catkin_ws/build/locosim/ros_impedance_controller/catkin_generated/installspace/ros_impedance_controllerConfig.cmake"
    "/home/utente/Robotics_ICE23_UNITN/catkin_ws/build/locosim/ros_impedance_controller/catkin_generated/installspace/ros_impedance_controllerConfig-version.cmake"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ros_impedance_controller" TYPE FILE FILES "/home/utente/Robotics_ICE23_UNITN/catkin_ws/src/locosim/ros_impedance_controller/package.xml")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/ros_impedance_controller" TYPE DIRECTORY FILES "/home/utente/Robotics_ICE23_UNITN/catkin_ws/src/locosim/ros_impedance_controller/include/ros_impedance_controller/")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libros_impedance_controller.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libros_impedance_controller.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libros_impedance_controller.so"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/home/utente/Robotics_ICE23_UNITN/catkin_ws/devel/lib/libros_impedance_controller.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libros_impedance_controller.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libros_impedance_controller.so")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libros_impedance_controller.so"
         OLD_RPATH "/opt/ros/noetic/lib:"
         NEW_RPATH "")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libros_impedance_controller.so")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ros_impedance_controller" TYPE FILE FILES "/home/utente/Robotics_ICE23_UNITN/catkin_ws/src/locosim/ros_impedance_controller/controller_plugin.xml")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ros_impedance_controller/launch" TYPE DIRECTORY FILES "/home/utente/Robotics_ICE23_UNITN/catkin_ws/src/locosim/ros_impedance_controller/launch/" REGEX "/\\.svn$" EXCLUDE)
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ros_impedance_controller/config" TYPE DIRECTORY FILES "/home/utente/Robotics_ICE23_UNITN/catkin_ws/src/locosim/ros_impedance_controller/config/" REGEX "/\\.svn$" EXCLUDE)
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ros_impedance_controller/worlds" TYPE DIRECTORY FILES "/home/utente/Robotics_ICE23_UNITN/catkin_ws/src/locosim/ros_impedance_controller/worlds/" REGEX "/\\.svn$" EXCLUDE)
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libros_impedance_controller.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libros_impedance_controller.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libros_impedance_controller.so"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/home/utente/Robotics_ICE23_UNITN/catkin_ws/devel/lib/libros_impedance_controller.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libros_impedance_controller.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libros_impedance_controller.so")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libros_impedance_controller.so"
         OLD_RPATH "/opt/ros/noetic/lib:"
         NEW_RPATH "")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libros_impedance_controller.so")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
endif()

