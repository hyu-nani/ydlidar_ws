# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "stereo_msgs: 1 messages, 0 services")

set(MSG_I_FLAGS "-Istereo_msgs:/home/pls/ydlidar_ws/src/ros/common_msgs/stereo_msgs/msg;-Isensor_msgs:/home/pls/ydlidar_ws/src/ros/common_msgs/sensor_msgs/msg;-Istd_msgs:/usr/share/std_msgs/cmake/../msg;-Igeometry_msgs:/home/pls/ydlidar_ws/src/ros/common_msgs/geometry_msgs/msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(genlisp REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(stereo_msgs_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/pls/ydlidar_ws/src/ros/common_msgs/stereo_msgs/msg/DisparityImage.msg" NAME_WE)
add_custom_target(_stereo_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "stereo_msgs" "/home/pls/ydlidar_ws/src/ros/common_msgs/stereo_msgs/msg/DisparityImage.msg" "sensor_msgs/Image:sensor_msgs/RegionOfInterest:std_msgs/Header"
)

#
#  langs = gencpp;genlisp;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(stereo_msgs
  "/home/pls/ydlidar_ws/src/ros/common_msgs/stereo_msgs/msg/DisparityImage.msg"
  "${MSG_I_FLAGS}"
  "/home/pls/ydlidar_ws/src/ros/common_msgs/sensor_msgs/msg/Image.msg;/home/pls/ydlidar_ws/src/ros/common_msgs/sensor_msgs/msg/RegionOfInterest.msg;/usr/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/stereo_msgs
)

### Generating Services

### Generating Module File
_generate_module_cpp(stereo_msgs
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/stereo_msgs
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(stereo_msgs_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(stereo_msgs_generate_messages stereo_msgs_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/pls/ydlidar_ws/src/ros/common_msgs/stereo_msgs/msg/DisparityImage.msg" NAME_WE)
add_dependencies(stereo_msgs_generate_messages_cpp _stereo_msgs_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(stereo_msgs_gencpp)
add_dependencies(stereo_msgs_gencpp stereo_msgs_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS stereo_msgs_generate_messages_cpp)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(stereo_msgs
  "/home/pls/ydlidar_ws/src/ros/common_msgs/stereo_msgs/msg/DisparityImage.msg"
  "${MSG_I_FLAGS}"
  "/home/pls/ydlidar_ws/src/ros/common_msgs/sensor_msgs/msg/Image.msg;/home/pls/ydlidar_ws/src/ros/common_msgs/sensor_msgs/msg/RegionOfInterest.msg;/usr/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/stereo_msgs
)

### Generating Services

### Generating Module File
_generate_module_lisp(stereo_msgs
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/stereo_msgs
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(stereo_msgs_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(stereo_msgs_generate_messages stereo_msgs_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/pls/ydlidar_ws/src/ros/common_msgs/stereo_msgs/msg/DisparityImage.msg" NAME_WE)
add_dependencies(stereo_msgs_generate_messages_lisp _stereo_msgs_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(stereo_msgs_genlisp)
add_dependencies(stereo_msgs_genlisp stereo_msgs_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS stereo_msgs_generate_messages_lisp)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(stereo_msgs
  "/home/pls/ydlidar_ws/src/ros/common_msgs/stereo_msgs/msg/DisparityImage.msg"
  "${MSG_I_FLAGS}"
  "/home/pls/ydlidar_ws/src/ros/common_msgs/sensor_msgs/msg/Image.msg;/home/pls/ydlidar_ws/src/ros/common_msgs/sensor_msgs/msg/RegionOfInterest.msg;/usr/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/stereo_msgs
)

### Generating Services

### Generating Module File
_generate_module_py(stereo_msgs
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/stereo_msgs
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(stereo_msgs_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(stereo_msgs_generate_messages stereo_msgs_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/pls/ydlidar_ws/src/ros/common_msgs/stereo_msgs/msg/DisparityImage.msg" NAME_WE)
add_dependencies(stereo_msgs_generate_messages_py _stereo_msgs_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(stereo_msgs_genpy)
add_dependencies(stereo_msgs_genpy stereo_msgs_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS stereo_msgs_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/stereo_msgs)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/stereo_msgs
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
if(TARGET sensor_msgs_generate_messages_cpp)
  add_dependencies(stereo_msgs_generate_messages_cpp sensor_msgs_generate_messages_cpp)
endif()
if(TARGET std_msgs_generate_messages_cpp)
  add_dependencies(stereo_msgs_generate_messages_cpp std_msgs_generate_messages_cpp)
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/stereo_msgs)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/stereo_msgs
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
if(TARGET sensor_msgs_generate_messages_lisp)
  add_dependencies(stereo_msgs_generate_messages_lisp sensor_msgs_generate_messages_lisp)
endif()
if(TARGET std_msgs_generate_messages_lisp)
  add_dependencies(stereo_msgs_generate_messages_lisp std_msgs_generate_messages_lisp)
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/stereo_msgs)
  install(CODE "execute_process(COMMAND \"/usr/bin/python3\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/stereo_msgs\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/stereo_msgs
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
if(TARGET sensor_msgs_generate_messages_py)
  add_dependencies(stereo_msgs_generate_messages_py sensor_msgs_generate_messages_py)
endif()
if(TARGET std_msgs_generate_messages_py)
  add_dependencies(stereo_msgs_generate_messages_py std_msgs_generate_messages_py)
endif()
