# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "visualization_msgs: 10 messages, 0 services")

set(MSG_I_FLAGS "-Ivisualization_msgs:/home/pls/ydlidar_ws/src/ros/common_msgs/visualization_msgs/msg;-Igeometry_msgs:/home/pls/ydlidar_ws/src/ros/common_msgs/geometry_msgs/msg;-Istd_msgs:/usr/share/std_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(genlisp REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(visualization_msgs_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/pls/ydlidar_ws/src/ros/common_msgs/visualization_msgs/msg/ImageMarker.msg" NAME_WE)
add_custom_target(_visualization_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "visualization_msgs" "/home/pls/ydlidar_ws/src/ros/common_msgs/visualization_msgs/msg/ImageMarker.msg" "std_msgs/Header:geometry_msgs/Point:std_msgs/ColorRGBA"
)

get_filename_component(_filename "/home/pls/ydlidar_ws/src/ros/common_msgs/visualization_msgs/msg/InteractiveMarker.msg" NAME_WE)
add_custom_target(_visualization_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "visualization_msgs" "/home/pls/ydlidar_ws/src/ros/common_msgs/visualization_msgs/msg/InteractiveMarker.msg" "visualization_msgs/MenuEntry:std_msgs/Header:visualization_msgs/InteractiveMarkerControl:geometry_msgs/Quaternion:std_msgs/ColorRGBA:geometry_msgs/Pose:geometry_msgs/Vector3:visualization_msgs/Marker:geometry_msgs/Point"
)

get_filename_component(_filename "/home/pls/ydlidar_ws/src/ros/common_msgs/visualization_msgs/msg/InteractiveMarkerControl.msg" NAME_WE)
add_custom_target(_visualization_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "visualization_msgs" "/home/pls/ydlidar_ws/src/ros/common_msgs/visualization_msgs/msg/InteractiveMarkerControl.msg" "std_msgs/Header:geometry_msgs/Quaternion:std_msgs/ColorRGBA:geometry_msgs/Pose:geometry_msgs/Vector3:visualization_msgs/Marker:geometry_msgs/Point"
)

get_filename_component(_filename "/home/pls/ydlidar_ws/src/ros/common_msgs/visualization_msgs/msg/InteractiveMarkerFeedback.msg" NAME_WE)
add_custom_target(_visualization_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "visualization_msgs" "/home/pls/ydlidar_ws/src/ros/common_msgs/visualization_msgs/msg/InteractiveMarkerFeedback.msg" "geometry_msgs/Pose:std_msgs/Header:geometry_msgs/Point:geometry_msgs/Quaternion"
)

get_filename_component(_filename "/home/pls/ydlidar_ws/src/ros/common_msgs/visualization_msgs/msg/InteractiveMarkerInit.msg" NAME_WE)
add_custom_target(_visualization_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "visualization_msgs" "/home/pls/ydlidar_ws/src/ros/common_msgs/visualization_msgs/msg/InteractiveMarkerInit.msg" "visualization_msgs/MenuEntry:std_msgs/Header:visualization_msgs/InteractiveMarkerControl:geometry_msgs/Quaternion:std_msgs/ColorRGBA:geometry_msgs/Pose:geometry_msgs/Vector3:visualization_msgs/Marker:geometry_msgs/Point:visualization_msgs/InteractiveMarker"
)

get_filename_component(_filename "/home/pls/ydlidar_ws/src/ros/common_msgs/visualization_msgs/msg/InteractiveMarkerPose.msg" NAME_WE)
add_custom_target(_visualization_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "visualization_msgs" "/home/pls/ydlidar_ws/src/ros/common_msgs/visualization_msgs/msg/InteractiveMarkerPose.msg" "geometry_msgs/Pose:std_msgs/Header:geometry_msgs/Point:geometry_msgs/Quaternion"
)

get_filename_component(_filename "/home/pls/ydlidar_ws/src/ros/common_msgs/visualization_msgs/msg/InteractiveMarkerUpdate.msg" NAME_WE)
add_custom_target(_visualization_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "visualization_msgs" "/home/pls/ydlidar_ws/src/ros/common_msgs/visualization_msgs/msg/InteractiveMarkerUpdate.msg" "visualization_msgs/MenuEntry:std_msgs/Header:visualization_msgs/InteractiveMarkerControl:geometry_msgs/Quaternion:std_msgs/ColorRGBA:geometry_msgs/Pose:geometry_msgs/Vector3:visualization_msgs/Marker:geometry_msgs/Point:visualization_msgs/InteractiveMarkerPose:visualization_msgs/InteractiveMarker"
)

get_filename_component(_filename "/home/pls/ydlidar_ws/src/ros/common_msgs/visualization_msgs/msg/MarkerArray.msg" NAME_WE)
add_custom_target(_visualization_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "visualization_msgs" "/home/pls/ydlidar_ws/src/ros/common_msgs/visualization_msgs/msg/MarkerArray.msg" "std_msgs/Header:geometry_msgs/Quaternion:std_msgs/ColorRGBA:geometry_msgs/Pose:geometry_msgs/Vector3:visualization_msgs/Marker:geometry_msgs/Point"
)

get_filename_component(_filename "/home/pls/ydlidar_ws/src/ros/common_msgs/visualization_msgs/msg/Marker.msg" NAME_WE)
add_custom_target(_visualization_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "visualization_msgs" "/home/pls/ydlidar_ws/src/ros/common_msgs/visualization_msgs/msg/Marker.msg" "std_msgs/Header:geometry_msgs/Quaternion:std_msgs/ColorRGBA:geometry_msgs/Pose:geometry_msgs/Vector3:geometry_msgs/Point"
)

get_filename_component(_filename "/home/pls/ydlidar_ws/src/ros/common_msgs/visualization_msgs/msg/MenuEntry.msg" NAME_WE)
add_custom_target(_visualization_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "visualization_msgs" "/home/pls/ydlidar_ws/src/ros/common_msgs/visualization_msgs/msg/MenuEntry.msg" ""
)

#
#  langs = gencpp;genlisp;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(visualization_msgs
  "/home/pls/ydlidar_ws/src/ros/common_msgs/visualization_msgs/msg/ImageMarker.msg"
  "${MSG_I_FLAGS}"
  "/usr/share/std_msgs/cmake/../msg/Header.msg;/home/pls/ydlidar_ws/src/ros/common_msgs/geometry_msgs/msg/Point.msg;/usr/share/std_msgs/cmake/../msg/ColorRGBA.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/visualization_msgs
)
_generate_msg_cpp(visualization_msgs
  "/home/pls/ydlidar_ws/src/ros/common_msgs/visualization_msgs/msg/InteractiveMarker.msg"
  "${MSG_I_FLAGS}"
  "/home/pls/ydlidar_ws/src/ros/common_msgs/visualization_msgs/msg/MenuEntry.msg;/usr/share/std_msgs/cmake/../msg/Header.msg;/home/pls/ydlidar_ws/src/ros/common_msgs/visualization_msgs/msg/InteractiveMarkerControl.msg;/home/pls/ydlidar_ws/src/ros/common_msgs/geometry_msgs/msg/Quaternion.msg;/usr/share/std_msgs/cmake/../msg/ColorRGBA.msg;/home/pls/ydlidar_ws/src/ros/common_msgs/geometry_msgs/msg/Pose.msg;/home/pls/ydlidar_ws/src/ros/common_msgs/geometry_msgs/msg/Vector3.msg;/home/pls/ydlidar_ws/src/ros/common_msgs/visualization_msgs/msg/Marker.msg;/home/pls/ydlidar_ws/src/ros/common_msgs/geometry_msgs/msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/visualization_msgs
)
_generate_msg_cpp(visualization_msgs
  "/home/pls/ydlidar_ws/src/ros/common_msgs/visualization_msgs/msg/InteractiveMarkerControl.msg"
  "${MSG_I_FLAGS}"
  "/usr/share/std_msgs/cmake/../msg/Header.msg;/home/pls/ydlidar_ws/src/ros/common_msgs/geometry_msgs/msg/Quaternion.msg;/usr/share/std_msgs/cmake/../msg/ColorRGBA.msg;/home/pls/ydlidar_ws/src/ros/common_msgs/geometry_msgs/msg/Pose.msg;/home/pls/ydlidar_ws/src/ros/common_msgs/geometry_msgs/msg/Vector3.msg;/home/pls/ydlidar_ws/src/ros/common_msgs/visualization_msgs/msg/Marker.msg;/home/pls/ydlidar_ws/src/ros/common_msgs/geometry_msgs/msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/visualization_msgs
)
_generate_msg_cpp(visualization_msgs
  "/home/pls/ydlidar_ws/src/ros/common_msgs/visualization_msgs/msg/InteractiveMarkerFeedback.msg"
  "${MSG_I_FLAGS}"
  "/home/pls/ydlidar_ws/src/ros/common_msgs/geometry_msgs/msg/Pose.msg;/usr/share/std_msgs/cmake/../msg/Header.msg;/home/pls/ydlidar_ws/src/ros/common_msgs/geometry_msgs/msg/Point.msg;/home/pls/ydlidar_ws/src/ros/common_msgs/geometry_msgs/msg/Quaternion.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/visualization_msgs
)
_generate_msg_cpp(visualization_msgs
  "/home/pls/ydlidar_ws/src/ros/common_msgs/visualization_msgs/msg/InteractiveMarkerInit.msg"
  "${MSG_I_FLAGS}"
  "/home/pls/ydlidar_ws/src/ros/common_msgs/visualization_msgs/msg/MenuEntry.msg;/usr/share/std_msgs/cmake/../msg/Header.msg;/home/pls/ydlidar_ws/src/ros/common_msgs/visualization_msgs/msg/InteractiveMarkerControl.msg;/home/pls/ydlidar_ws/src/ros/common_msgs/geometry_msgs/msg/Quaternion.msg;/usr/share/std_msgs/cmake/../msg/ColorRGBA.msg;/home/pls/ydlidar_ws/src/ros/common_msgs/geometry_msgs/msg/Pose.msg;/home/pls/ydlidar_ws/src/ros/common_msgs/geometry_msgs/msg/Vector3.msg;/home/pls/ydlidar_ws/src/ros/common_msgs/visualization_msgs/msg/Marker.msg;/home/pls/ydlidar_ws/src/ros/common_msgs/geometry_msgs/msg/Point.msg;/home/pls/ydlidar_ws/src/ros/common_msgs/visualization_msgs/msg/InteractiveMarker.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/visualization_msgs
)
_generate_msg_cpp(visualization_msgs
  "/home/pls/ydlidar_ws/src/ros/common_msgs/visualization_msgs/msg/InteractiveMarkerPose.msg"
  "${MSG_I_FLAGS}"
  "/home/pls/ydlidar_ws/src/ros/common_msgs/geometry_msgs/msg/Pose.msg;/usr/share/std_msgs/cmake/../msg/Header.msg;/home/pls/ydlidar_ws/src/ros/common_msgs/geometry_msgs/msg/Point.msg;/home/pls/ydlidar_ws/src/ros/common_msgs/geometry_msgs/msg/Quaternion.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/visualization_msgs
)
_generate_msg_cpp(visualization_msgs
  "/home/pls/ydlidar_ws/src/ros/common_msgs/visualization_msgs/msg/InteractiveMarkerUpdate.msg"
  "${MSG_I_FLAGS}"
  "/home/pls/ydlidar_ws/src/ros/common_msgs/visualization_msgs/msg/MenuEntry.msg;/usr/share/std_msgs/cmake/../msg/Header.msg;/home/pls/ydlidar_ws/src/ros/common_msgs/visualization_msgs/msg/InteractiveMarkerControl.msg;/home/pls/ydlidar_ws/src/ros/common_msgs/geometry_msgs/msg/Quaternion.msg;/usr/share/std_msgs/cmake/../msg/ColorRGBA.msg;/home/pls/ydlidar_ws/src/ros/common_msgs/geometry_msgs/msg/Pose.msg;/home/pls/ydlidar_ws/src/ros/common_msgs/geometry_msgs/msg/Vector3.msg;/home/pls/ydlidar_ws/src/ros/common_msgs/visualization_msgs/msg/Marker.msg;/home/pls/ydlidar_ws/src/ros/common_msgs/geometry_msgs/msg/Point.msg;/home/pls/ydlidar_ws/src/ros/common_msgs/visualization_msgs/msg/InteractiveMarkerPose.msg;/home/pls/ydlidar_ws/src/ros/common_msgs/visualization_msgs/msg/InteractiveMarker.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/visualization_msgs
)
_generate_msg_cpp(visualization_msgs
  "/home/pls/ydlidar_ws/src/ros/common_msgs/visualization_msgs/msg/MarkerArray.msg"
  "${MSG_I_FLAGS}"
  "/usr/share/std_msgs/cmake/../msg/Header.msg;/home/pls/ydlidar_ws/src/ros/common_msgs/geometry_msgs/msg/Quaternion.msg;/usr/share/std_msgs/cmake/../msg/ColorRGBA.msg;/home/pls/ydlidar_ws/src/ros/common_msgs/geometry_msgs/msg/Pose.msg;/home/pls/ydlidar_ws/src/ros/common_msgs/geometry_msgs/msg/Vector3.msg;/home/pls/ydlidar_ws/src/ros/common_msgs/visualization_msgs/msg/Marker.msg;/home/pls/ydlidar_ws/src/ros/common_msgs/geometry_msgs/msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/visualization_msgs
)
_generate_msg_cpp(visualization_msgs
  "/home/pls/ydlidar_ws/src/ros/common_msgs/visualization_msgs/msg/Marker.msg"
  "${MSG_I_FLAGS}"
  "/usr/share/std_msgs/cmake/../msg/Header.msg;/home/pls/ydlidar_ws/src/ros/common_msgs/geometry_msgs/msg/Quaternion.msg;/usr/share/std_msgs/cmake/../msg/ColorRGBA.msg;/home/pls/ydlidar_ws/src/ros/common_msgs/geometry_msgs/msg/Pose.msg;/home/pls/ydlidar_ws/src/ros/common_msgs/geometry_msgs/msg/Vector3.msg;/home/pls/ydlidar_ws/src/ros/common_msgs/geometry_msgs/msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/visualization_msgs
)
_generate_msg_cpp(visualization_msgs
  "/home/pls/ydlidar_ws/src/ros/common_msgs/visualization_msgs/msg/MenuEntry.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/visualization_msgs
)

### Generating Services

### Generating Module File
_generate_module_cpp(visualization_msgs
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/visualization_msgs
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(visualization_msgs_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(visualization_msgs_generate_messages visualization_msgs_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/pls/ydlidar_ws/src/ros/common_msgs/visualization_msgs/msg/ImageMarker.msg" NAME_WE)
add_dependencies(visualization_msgs_generate_messages_cpp _visualization_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pls/ydlidar_ws/src/ros/common_msgs/visualization_msgs/msg/InteractiveMarker.msg" NAME_WE)
add_dependencies(visualization_msgs_generate_messages_cpp _visualization_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pls/ydlidar_ws/src/ros/common_msgs/visualization_msgs/msg/InteractiveMarkerControl.msg" NAME_WE)
add_dependencies(visualization_msgs_generate_messages_cpp _visualization_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pls/ydlidar_ws/src/ros/common_msgs/visualization_msgs/msg/InteractiveMarkerFeedback.msg" NAME_WE)
add_dependencies(visualization_msgs_generate_messages_cpp _visualization_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pls/ydlidar_ws/src/ros/common_msgs/visualization_msgs/msg/InteractiveMarkerInit.msg" NAME_WE)
add_dependencies(visualization_msgs_generate_messages_cpp _visualization_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pls/ydlidar_ws/src/ros/common_msgs/visualization_msgs/msg/InteractiveMarkerPose.msg" NAME_WE)
add_dependencies(visualization_msgs_generate_messages_cpp _visualization_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pls/ydlidar_ws/src/ros/common_msgs/visualization_msgs/msg/InteractiveMarkerUpdate.msg" NAME_WE)
add_dependencies(visualization_msgs_generate_messages_cpp _visualization_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pls/ydlidar_ws/src/ros/common_msgs/visualization_msgs/msg/MarkerArray.msg" NAME_WE)
add_dependencies(visualization_msgs_generate_messages_cpp _visualization_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pls/ydlidar_ws/src/ros/common_msgs/visualization_msgs/msg/Marker.msg" NAME_WE)
add_dependencies(visualization_msgs_generate_messages_cpp _visualization_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pls/ydlidar_ws/src/ros/common_msgs/visualization_msgs/msg/MenuEntry.msg" NAME_WE)
add_dependencies(visualization_msgs_generate_messages_cpp _visualization_msgs_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(visualization_msgs_gencpp)
add_dependencies(visualization_msgs_gencpp visualization_msgs_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS visualization_msgs_generate_messages_cpp)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(visualization_msgs
  "/home/pls/ydlidar_ws/src/ros/common_msgs/visualization_msgs/msg/ImageMarker.msg"
  "${MSG_I_FLAGS}"
  "/usr/share/std_msgs/cmake/../msg/Header.msg;/home/pls/ydlidar_ws/src/ros/common_msgs/geometry_msgs/msg/Point.msg;/usr/share/std_msgs/cmake/../msg/ColorRGBA.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/visualization_msgs
)
_generate_msg_lisp(visualization_msgs
  "/home/pls/ydlidar_ws/src/ros/common_msgs/visualization_msgs/msg/InteractiveMarker.msg"
  "${MSG_I_FLAGS}"
  "/home/pls/ydlidar_ws/src/ros/common_msgs/visualization_msgs/msg/MenuEntry.msg;/usr/share/std_msgs/cmake/../msg/Header.msg;/home/pls/ydlidar_ws/src/ros/common_msgs/visualization_msgs/msg/InteractiveMarkerControl.msg;/home/pls/ydlidar_ws/src/ros/common_msgs/geometry_msgs/msg/Quaternion.msg;/usr/share/std_msgs/cmake/../msg/ColorRGBA.msg;/home/pls/ydlidar_ws/src/ros/common_msgs/geometry_msgs/msg/Pose.msg;/home/pls/ydlidar_ws/src/ros/common_msgs/geometry_msgs/msg/Vector3.msg;/home/pls/ydlidar_ws/src/ros/common_msgs/visualization_msgs/msg/Marker.msg;/home/pls/ydlidar_ws/src/ros/common_msgs/geometry_msgs/msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/visualization_msgs
)
_generate_msg_lisp(visualization_msgs
  "/home/pls/ydlidar_ws/src/ros/common_msgs/visualization_msgs/msg/InteractiveMarkerControl.msg"
  "${MSG_I_FLAGS}"
  "/usr/share/std_msgs/cmake/../msg/Header.msg;/home/pls/ydlidar_ws/src/ros/common_msgs/geometry_msgs/msg/Quaternion.msg;/usr/share/std_msgs/cmake/../msg/ColorRGBA.msg;/home/pls/ydlidar_ws/src/ros/common_msgs/geometry_msgs/msg/Pose.msg;/home/pls/ydlidar_ws/src/ros/common_msgs/geometry_msgs/msg/Vector3.msg;/home/pls/ydlidar_ws/src/ros/common_msgs/visualization_msgs/msg/Marker.msg;/home/pls/ydlidar_ws/src/ros/common_msgs/geometry_msgs/msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/visualization_msgs
)
_generate_msg_lisp(visualization_msgs
  "/home/pls/ydlidar_ws/src/ros/common_msgs/visualization_msgs/msg/InteractiveMarkerFeedback.msg"
  "${MSG_I_FLAGS}"
  "/home/pls/ydlidar_ws/src/ros/common_msgs/geometry_msgs/msg/Pose.msg;/usr/share/std_msgs/cmake/../msg/Header.msg;/home/pls/ydlidar_ws/src/ros/common_msgs/geometry_msgs/msg/Point.msg;/home/pls/ydlidar_ws/src/ros/common_msgs/geometry_msgs/msg/Quaternion.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/visualization_msgs
)
_generate_msg_lisp(visualization_msgs
  "/home/pls/ydlidar_ws/src/ros/common_msgs/visualization_msgs/msg/InteractiveMarkerInit.msg"
  "${MSG_I_FLAGS}"
  "/home/pls/ydlidar_ws/src/ros/common_msgs/visualization_msgs/msg/MenuEntry.msg;/usr/share/std_msgs/cmake/../msg/Header.msg;/home/pls/ydlidar_ws/src/ros/common_msgs/visualization_msgs/msg/InteractiveMarkerControl.msg;/home/pls/ydlidar_ws/src/ros/common_msgs/geometry_msgs/msg/Quaternion.msg;/usr/share/std_msgs/cmake/../msg/ColorRGBA.msg;/home/pls/ydlidar_ws/src/ros/common_msgs/geometry_msgs/msg/Pose.msg;/home/pls/ydlidar_ws/src/ros/common_msgs/geometry_msgs/msg/Vector3.msg;/home/pls/ydlidar_ws/src/ros/common_msgs/visualization_msgs/msg/Marker.msg;/home/pls/ydlidar_ws/src/ros/common_msgs/geometry_msgs/msg/Point.msg;/home/pls/ydlidar_ws/src/ros/common_msgs/visualization_msgs/msg/InteractiveMarker.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/visualization_msgs
)
_generate_msg_lisp(visualization_msgs
  "/home/pls/ydlidar_ws/src/ros/common_msgs/visualization_msgs/msg/InteractiveMarkerPose.msg"
  "${MSG_I_FLAGS}"
  "/home/pls/ydlidar_ws/src/ros/common_msgs/geometry_msgs/msg/Pose.msg;/usr/share/std_msgs/cmake/../msg/Header.msg;/home/pls/ydlidar_ws/src/ros/common_msgs/geometry_msgs/msg/Point.msg;/home/pls/ydlidar_ws/src/ros/common_msgs/geometry_msgs/msg/Quaternion.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/visualization_msgs
)
_generate_msg_lisp(visualization_msgs
  "/home/pls/ydlidar_ws/src/ros/common_msgs/visualization_msgs/msg/InteractiveMarkerUpdate.msg"
  "${MSG_I_FLAGS}"
  "/home/pls/ydlidar_ws/src/ros/common_msgs/visualization_msgs/msg/MenuEntry.msg;/usr/share/std_msgs/cmake/../msg/Header.msg;/home/pls/ydlidar_ws/src/ros/common_msgs/visualization_msgs/msg/InteractiveMarkerControl.msg;/home/pls/ydlidar_ws/src/ros/common_msgs/geometry_msgs/msg/Quaternion.msg;/usr/share/std_msgs/cmake/../msg/ColorRGBA.msg;/home/pls/ydlidar_ws/src/ros/common_msgs/geometry_msgs/msg/Pose.msg;/home/pls/ydlidar_ws/src/ros/common_msgs/geometry_msgs/msg/Vector3.msg;/home/pls/ydlidar_ws/src/ros/common_msgs/visualization_msgs/msg/Marker.msg;/home/pls/ydlidar_ws/src/ros/common_msgs/geometry_msgs/msg/Point.msg;/home/pls/ydlidar_ws/src/ros/common_msgs/visualization_msgs/msg/InteractiveMarkerPose.msg;/home/pls/ydlidar_ws/src/ros/common_msgs/visualization_msgs/msg/InteractiveMarker.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/visualization_msgs
)
_generate_msg_lisp(visualization_msgs
  "/home/pls/ydlidar_ws/src/ros/common_msgs/visualization_msgs/msg/MarkerArray.msg"
  "${MSG_I_FLAGS}"
  "/usr/share/std_msgs/cmake/../msg/Header.msg;/home/pls/ydlidar_ws/src/ros/common_msgs/geometry_msgs/msg/Quaternion.msg;/usr/share/std_msgs/cmake/../msg/ColorRGBA.msg;/home/pls/ydlidar_ws/src/ros/common_msgs/geometry_msgs/msg/Pose.msg;/home/pls/ydlidar_ws/src/ros/common_msgs/geometry_msgs/msg/Vector3.msg;/home/pls/ydlidar_ws/src/ros/common_msgs/visualization_msgs/msg/Marker.msg;/home/pls/ydlidar_ws/src/ros/common_msgs/geometry_msgs/msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/visualization_msgs
)
_generate_msg_lisp(visualization_msgs
  "/home/pls/ydlidar_ws/src/ros/common_msgs/visualization_msgs/msg/Marker.msg"
  "${MSG_I_FLAGS}"
  "/usr/share/std_msgs/cmake/../msg/Header.msg;/home/pls/ydlidar_ws/src/ros/common_msgs/geometry_msgs/msg/Quaternion.msg;/usr/share/std_msgs/cmake/../msg/ColorRGBA.msg;/home/pls/ydlidar_ws/src/ros/common_msgs/geometry_msgs/msg/Pose.msg;/home/pls/ydlidar_ws/src/ros/common_msgs/geometry_msgs/msg/Vector3.msg;/home/pls/ydlidar_ws/src/ros/common_msgs/geometry_msgs/msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/visualization_msgs
)
_generate_msg_lisp(visualization_msgs
  "/home/pls/ydlidar_ws/src/ros/common_msgs/visualization_msgs/msg/MenuEntry.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/visualization_msgs
)

### Generating Services

### Generating Module File
_generate_module_lisp(visualization_msgs
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/visualization_msgs
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(visualization_msgs_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(visualization_msgs_generate_messages visualization_msgs_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/pls/ydlidar_ws/src/ros/common_msgs/visualization_msgs/msg/ImageMarker.msg" NAME_WE)
add_dependencies(visualization_msgs_generate_messages_lisp _visualization_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pls/ydlidar_ws/src/ros/common_msgs/visualization_msgs/msg/InteractiveMarker.msg" NAME_WE)
add_dependencies(visualization_msgs_generate_messages_lisp _visualization_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pls/ydlidar_ws/src/ros/common_msgs/visualization_msgs/msg/InteractiveMarkerControl.msg" NAME_WE)
add_dependencies(visualization_msgs_generate_messages_lisp _visualization_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pls/ydlidar_ws/src/ros/common_msgs/visualization_msgs/msg/InteractiveMarkerFeedback.msg" NAME_WE)
add_dependencies(visualization_msgs_generate_messages_lisp _visualization_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pls/ydlidar_ws/src/ros/common_msgs/visualization_msgs/msg/InteractiveMarkerInit.msg" NAME_WE)
add_dependencies(visualization_msgs_generate_messages_lisp _visualization_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pls/ydlidar_ws/src/ros/common_msgs/visualization_msgs/msg/InteractiveMarkerPose.msg" NAME_WE)
add_dependencies(visualization_msgs_generate_messages_lisp _visualization_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pls/ydlidar_ws/src/ros/common_msgs/visualization_msgs/msg/InteractiveMarkerUpdate.msg" NAME_WE)
add_dependencies(visualization_msgs_generate_messages_lisp _visualization_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pls/ydlidar_ws/src/ros/common_msgs/visualization_msgs/msg/MarkerArray.msg" NAME_WE)
add_dependencies(visualization_msgs_generate_messages_lisp _visualization_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pls/ydlidar_ws/src/ros/common_msgs/visualization_msgs/msg/Marker.msg" NAME_WE)
add_dependencies(visualization_msgs_generate_messages_lisp _visualization_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pls/ydlidar_ws/src/ros/common_msgs/visualization_msgs/msg/MenuEntry.msg" NAME_WE)
add_dependencies(visualization_msgs_generate_messages_lisp _visualization_msgs_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(visualization_msgs_genlisp)
add_dependencies(visualization_msgs_genlisp visualization_msgs_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS visualization_msgs_generate_messages_lisp)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(visualization_msgs
  "/home/pls/ydlidar_ws/src/ros/common_msgs/visualization_msgs/msg/ImageMarker.msg"
  "${MSG_I_FLAGS}"
  "/usr/share/std_msgs/cmake/../msg/Header.msg;/home/pls/ydlidar_ws/src/ros/common_msgs/geometry_msgs/msg/Point.msg;/usr/share/std_msgs/cmake/../msg/ColorRGBA.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/visualization_msgs
)
_generate_msg_py(visualization_msgs
  "/home/pls/ydlidar_ws/src/ros/common_msgs/visualization_msgs/msg/InteractiveMarker.msg"
  "${MSG_I_FLAGS}"
  "/home/pls/ydlidar_ws/src/ros/common_msgs/visualization_msgs/msg/MenuEntry.msg;/usr/share/std_msgs/cmake/../msg/Header.msg;/home/pls/ydlidar_ws/src/ros/common_msgs/visualization_msgs/msg/InteractiveMarkerControl.msg;/home/pls/ydlidar_ws/src/ros/common_msgs/geometry_msgs/msg/Quaternion.msg;/usr/share/std_msgs/cmake/../msg/ColorRGBA.msg;/home/pls/ydlidar_ws/src/ros/common_msgs/geometry_msgs/msg/Pose.msg;/home/pls/ydlidar_ws/src/ros/common_msgs/geometry_msgs/msg/Vector3.msg;/home/pls/ydlidar_ws/src/ros/common_msgs/visualization_msgs/msg/Marker.msg;/home/pls/ydlidar_ws/src/ros/common_msgs/geometry_msgs/msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/visualization_msgs
)
_generate_msg_py(visualization_msgs
  "/home/pls/ydlidar_ws/src/ros/common_msgs/visualization_msgs/msg/InteractiveMarkerControl.msg"
  "${MSG_I_FLAGS}"
  "/usr/share/std_msgs/cmake/../msg/Header.msg;/home/pls/ydlidar_ws/src/ros/common_msgs/geometry_msgs/msg/Quaternion.msg;/usr/share/std_msgs/cmake/../msg/ColorRGBA.msg;/home/pls/ydlidar_ws/src/ros/common_msgs/geometry_msgs/msg/Pose.msg;/home/pls/ydlidar_ws/src/ros/common_msgs/geometry_msgs/msg/Vector3.msg;/home/pls/ydlidar_ws/src/ros/common_msgs/visualization_msgs/msg/Marker.msg;/home/pls/ydlidar_ws/src/ros/common_msgs/geometry_msgs/msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/visualization_msgs
)
_generate_msg_py(visualization_msgs
  "/home/pls/ydlidar_ws/src/ros/common_msgs/visualization_msgs/msg/InteractiveMarkerFeedback.msg"
  "${MSG_I_FLAGS}"
  "/home/pls/ydlidar_ws/src/ros/common_msgs/geometry_msgs/msg/Pose.msg;/usr/share/std_msgs/cmake/../msg/Header.msg;/home/pls/ydlidar_ws/src/ros/common_msgs/geometry_msgs/msg/Point.msg;/home/pls/ydlidar_ws/src/ros/common_msgs/geometry_msgs/msg/Quaternion.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/visualization_msgs
)
_generate_msg_py(visualization_msgs
  "/home/pls/ydlidar_ws/src/ros/common_msgs/visualization_msgs/msg/InteractiveMarkerInit.msg"
  "${MSG_I_FLAGS}"
  "/home/pls/ydlidar_ws/src/ros/common_msgs/visualization_msgs/msg/MenuEntry.msg;/usr/share/std_msgs/cmake/../msg/Header.msg;/home/pls/ydlidar_ws/src/ros/common_msgs/visualization_msgs/msg/InteractiveMarkerControl.msg;/home/pls/ydlidar_ws/src/ros/common_msgs/geometry_msgs/msg/Quaternion.msg;/usr/share/std_msgs/cmake/../msg/ColorRGBA.msg;/home/pls/ydlidar_ws/src/ros/common_msgs/geometry_msgs/msg/Pose.msg;/home/pls/ydlidar_ws/src/ros/common_msgs/geometry_msgs/msg/Vector3.msg;/home/pls/ydlidar_ws/src/ros/common_msgs/visualization_msgs/msg/Marker.msg;/home/pls/ydlidar_ws/src/ros/common_msgs/geometry_msgs/msg/Point.msg;/home/pls/ydlidar_ws/src/ros/common_msgs/visualization_msgs/msg/InteractiveMarker.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/visualization_msgs
)
_generate_msg_py(visualization_msgs
  "/home/pls/ydlidar_ws/src/ros/common_msgs/visualization_msgs/msg/InteractiveMarkerPose.msg"
  "${MSG_I_FLAGS}"
  "/home/pls/ydlidar_ws/src/ros/common_msgs/geometry_msgs/msg/Pose.msg;/usr/share/std_msgs/cmake/../msg/Header.msg;/home/pls/ydlidar_ws/src/ros/common_msgs/geometry_msgs/msg/Point.msg;/home/pls/ydlidar_ws/src/ros/common_msgs/geometry_msgs/msg/Quaternion.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/visualization_msgs
)
_generate_msg_py(visualization_msgs
  "/home/pls/ydlidar_ws/src/ros/common_msgs/visualization_msgs/msg/InteractiveMarkerUpdate.msg"
  "${MSG_I_FLAGS}"
  "/home/pls/ydlidar_ws/src/ros/common_msgs/visualization_msgs/msg/MenuEntry.msg;/usr/share/std_msgs/cmake/../msg/Header.msg;/home/pls/ydlidar_ws/src/ros/common_msgs/visualization_msgs/msg/InteractiveMarkerControl.msg;/home/pls/ydlidar_ws/src/ros/common_msgs/geometry_msgs/msg/Quaternion.msg;/usr/share/std_msgs/cmake/../msg/ColorRGBA.msg;/home/pls/ydlidar_ws/src/ros/common_msgs/geometry_msgs/msg/Pose.msg;/home/pls/ydlidar_ws/src/ros/common_msgs/geometry_msgs/msg/Vector3.msg;/home/pls/ydlidar_ws/src/ros/common_msgs/visualization_msgs/msg/Marker.msg;/home/pls/ydlidar_ws/src/ros/common_msgs/geometry_msgs/msg/Point.msg;/home/pls/ydlidar_ws/src/ros/common_msgs/visualization_msgs/msg/InteractiveMarkerPose.msg;/home/pls/ydlidar_ws/src/ros/common_msgs/visualization_msgs/msg/InteractiveMarker.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/visualization_msgs
)
_generate_msg_py(visualization_msgs
  "/home/pls/ydlidar_ws/src/ros/common_msgs/visualization_msgs/msg/MarkerArray.msg"
  "${MSG_I_FLAGS}"
  "/usr/share/std_msgs/cmake/../msg/Header.msg;/home/pls/ydlidar_ws/src/ros/common_msgs/geometry_msgs/msg/Quaternion.msg;/usr/share/std_msgs/cmake/../msg/ColorRGBA.msg;/home/pls/ydlidar_ws/src/ros/common_msgs/geometry_msgs/msg/Pose.msg;/home/pls/ydlidar_ws/src/ros/common_msgs/geometry_msgs/msg/Vector3.msg;/home/pls/ydlidar_ws/src/ros/common_msgs/visualization_msgs/msg/Marker.msg;/home/pls/ydlidar_ws/src/ros/common_msgs/geometry_msgs/msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/visualization_msgs
)
_generate_msg_py(visualization_msgs
  "/home/pls/ydlidar_ws/src/ros/common_msgs/visualization_msgs/msg/Marker.msg"
  "${MSG_I_FLAGS}"
  "/usr/share/std_msgs/cmake/../msg/Header.msg;/home/pls/ydlidar_ws/src/ros/common_msgs/geometry_msgs/msg/Quaternion.msg;/usr/share/std_msgs/cmake/../msg/ColorRGBA.msg;/home/pls/ydlidar_ws/src/ros/common_msgs/geometry_msgs/msg/Pose.msg;/home/pls/ydlidar_ws/src/ros/common_msgs/geometry_msgs/msg/Vector3.msg;/home/pls/ydlidar_ws/src/ros/common_msgs/geometry_msgs/msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/visualization_msgs
)
_generate_msg_py(visualization_msgs
  "/home/pls/ydlidar_ws/src/ros/common_msgs/visualization_msgs/msg/MenuEntry.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/visualization_msgs
)

### Generating Services

### Generating Module File
_generate_module_py(visualization_msgs
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/visualization_msgs
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(visualization_msgs_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(visualization_msgs_generate_messages visualization_msgs_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/pls/ydlidar_ws/src/ros/common_msgs/visualization_msgs/msg/ImageMarker.msg" NAME_WE)
add_dependencies(visualization_msgs_generate_messages_py _visualization_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pls/ydlidar_ws/src/ros/common_msgs/visualization_msgs/msg/InteractiveMarker.msg" NAME_WE)
add_dependencies(visualization_msgs_generate_messages_py _visualization_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pls/ydlidar_ws/src/ros/common_msgs/visualization_msgs/msg/InteractiveMarkerControl.msg" NAME_WE)
add_dependencies(visualization_msgs_generate_messages_py _visualization_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pls/ydlidar_ws/src/ros/common_msgs/visualization_msgs/msg/InteractiveMarkerFeedback.msg" NAME_WE)
add_dependencies(visualization_msgs_generate_messages_py _visualization_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pls/ydlidar_ws/src/ros/common_msgs/visualization_msgs/msg/InteractiveMarkerInit.msg" NAME_WE)
add_dependencies(visualization_msgs_generate_messages_py _visualization_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pls/ydlidar_ws/src/ros/common_msgs/visualization_msgs/msg/InteractiveMarkerPose.msg" NAME_WE)
add_dependencies(visualization_msgs_generate_messages_py _visualization_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pls/ydlidar_ws/src/ros/common_msgs/visualization_msgs/msg/InteractiveMarkerUpdate.msg" NAME_WE)
add_dependencies(visualization_msgs_generate_messages_py _visualization_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pls/ydlidar_ws/src/ros/common_msgs/visualization_msgs/msg/MarkerArray.msg" NAME_WE)
add_dependencies(visualization_msgs_generate_messages_py _visualization_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pls/ydlidar_ws/src/ros/common_msgs/visualization_msgs/msg/Marker.msg" NAME_WE)
add_dependencies(visualization_msgs_generate_messages_py _visualization_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pls/ydlidar_ws/src/ros/common_msgs/visualization_msgs/msg/MenuEntry.msg" NAME_WE)
add_dependencies(visualization_msgs_generate_messages_py _visualization_msgs_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(visualization_msgs_genpy)
add_dependencies(visualization_msgs_genpy visualization_msgs_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS visualization_msgs_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/visualization_msgs)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/visualization_msgs
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
if(TARGET geometry_msgs_generate_messages_cpp)
  add_dependencies(visualization_msgs_generate_messages_cpp geometry_msgs_generate_messages_cpp)
endif()
if(TARGET std_msgs_generate_messages_cpp)
  add_dependencies(visualization_msgs_generate_messages_cpp std_msgs_generate_messages_cpp)
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/visualization_msgs)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/visualization_msgs
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
if(TARGET geometry_msgs_generate_messages_lisp)
  add_dependencies(visualization_msgs_generate_messages_lisp geometry_msgs_generate_messages_lisp)
endif()
if(TARGET std_msgs_generate_messages_lisp)
  add_dependencies(visualization_msgs_generate_messages_lisp std_msgs_generate_messages_lisp)
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/visualization_msgs)
  install(CODE "execute_process(COMMAND \"/usr/bin/python3\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/visualization_msgs\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/visualization_msgs
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
if(TARGET geometry_msgs_generate_messages_py)
  add_dependencies(visualization_msgs_generate_messages_py geometry_msgs_generate_messages_py)
endif()
if(TARGET std_msgs_generate_messages_py)
  add_dependencies(visualization_msgs_generate_messages_py std_msgs_generate_messages_py)
endif()
