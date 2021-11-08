# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "shape_msgs: 4 messages, 0 services")

set(MSG_I_FLAGS "-Ishape_msgs:/home/pls/ydlidar_ws/src/ros/common_msgs/shape_msgs/msg;-Igeometry_msgs:/home/pls/ydlidar_ws/src/ros/common_msgs/geometry_msgs/msg;-Istd_msgs:/usr/share/std_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(genlisp REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(shape_msgs_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/pls/ydlidar_ws/src/ros/common_msgs/shape_msgs/msg/Mesh.msg" NAME_WE)
add_custom_target(_shape_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "shape_msgs" "/home/pls/ydlidar_ws/src/ros/common_msgs/shape_msgs/msg/Mesh.msg" "shape_msgs/MeshTriangle:geometry_msgs/Point"
)

get_filename_component(_filename "/home/pls/ydlidar_ws/src/ros/common_msgs/shape_msgs/msg/MeshTriangle.msg" NAME_WE)
add_custom_target(_shape_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "shape_msgs" "/home/pls/ydlidar_ws/src/ros/common_msgs/shape_msgs/msg/MeshTriangle.msg" ""
)

get_filename_component(_filename "/home/pls/ydlidar_ws/src/ros/common_msgs/shape_msgs/msg/Plane.msg" NAME_WE)
add_custom_target(_shape_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "shape_msgs" "/home/pls/ydlidar_ws/src/ros/common_msgs/shape_msgs/msg/Plane.msg" ""
)

get_filename_component(_filename "/home/pls/ydlidar_ws/src/ros/common_msgs/shape_msgs/msg/SolidPrimitive.msg" NAME_WE)
add_custom_target(_shape_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "shape_msgs" "/home/pls/ydlidar_ws/src/ros/common_msgs/shape_msgs/msg/SolidPrimitive.msg" ""
)

#
#  langs = gencpp;genlisp;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(shape_msgs
  "/home/pls/ydlidar_ws/src/ros/common_msgs/shape_msgs/msg/Mesh.msg"
  "${MSG_I_FLAGS}"
  "/home/pls/ydlidar_ws/src/ros/common_msgs/shape_msgs/msg/MeshTriangle.msg;/home/pls/ydlidar_ws/src/ros/common_msgs/geometry_msgs/msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/shape_msgs
)
_generate_msg_cpp(shape_msgs
  "/home/pls/ydlidar_ws/src/ros/common_msgs/shape_msgs/msg/MeshTriangle.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/shape_msgs
)
_generate_msg_cpp(shape_msgs
  "/home/pls/ydlidar_ws/src/ros/common_msgs/shape_msgs/msg/Plane.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/shape_msgs
)
_generate_msg_cpp(shape_msgs
  "/home/pls/ydlidar_ws/src/ros/common_msgs/shape_msgs/msg/SolidPrimitive.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/shape_msgs
)

### Generating Services

### Generating Module File
_generate_module_cpp(shape_msgs
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/shape_msgs
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(shape_msgs_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(shape_msgs_generate_messages shape_msgs_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/pls/ydlidar_ws/src/ros/common_msgs/shape_msgs/msg/Mesh.msg" NAME_WE)
add_dependencies(shape_msgs_generate_messages_cpp _shape_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pls/ydlidar_ws/src/ros/common_msgs/shape_msgs/msg/MeshTriangle.msg" NAME_WE)
add_dependencies(shape_msgs_generate_messages_cpp _shape_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pls/ydlidar_ws/src/ros/common_msgs/shape_msgs/msg/Plane.msg" NAME_WE)
add_dependencies(shape_msgs_generate_messages_cpp _shape_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pls/ydlidar_ws/src/ros/common_msgs/shape_msgs/msg/SolidPrimitive.msg" NAME_WE)
add_dependencies(shape_msgs_generate_messages_cpp _shape_msgs_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(shape_msgs_gencpp)
add_dependencies(shape_msgs_gencpp shape_msgs_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS shape_msgs_generate_messages_cpp)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(shape_msgs
  "/home/pls/ydlidar_ws/src/ros/common_msgs/shape_msgs/msg/Mesh.msg"
  "${MSG_I_FLAGS}"
  "/home/pls/ydlidar_ws/src/ros/common_msgs/shape_msgs/msg/MeshTriangle.msg;/home/pls/ydlidar_ws/src/ros/common_msgs/geometry_msgs/msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/shape_msgs
)
_generate_msg_lisp(shape_msgs
  "/home/pls/ydlidar_ws/src/ros/common_msgs/shape_msgs/msg/MeshTriangle.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/shape_msgs
)
_generate_msg_lisp(shape_msgs
  "/home/pls/ydlidar_ws/src/ros/common_msgs/shape_msgs/msg/Plane.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/shape_msgs
)
_generate_msg_lisp(shape_msgs
  "/home/pls/ydlidar_ws/src/ros/common_msgs/shape_msgs/msg/SolidPrimitive.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/shape_msgs
)

### Generating Services

### Generating Module File
_generate_module_lisp(shape_msgs
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/shape_msgs
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(shape_msgs_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(shape_msgs_generate_messages shape_msgs_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/pls/ydlidar_ws/src/ros/common_msgs/shape_msgs/msg/Mesh.msg" NAME_WE)
add_dependencies(shape_msgs_generate_messages_lisp _shape_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pls/ydlidar_ws/src/ros/common_msgs/shape_msgs/msg/MeshTriangle.msg" NAME_WE)
add_dependencies(shape_msgs_generate_messages_lisp _shape_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pls/ydlidar_ws/src/ros/common_msgs/shape_msgs/msg/Plane.msg" NAME_WE)
add_dependencies(shape_msgs_generate_messages_lisp _shape_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pls/ydlidar_ws/src/ros/common_msgs/shape_msgs/msg/SolidPrimitive.msg" NAME_WE)
add_dependencies(shape_msgs_generate_messages_lisp _shape_msgs_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(shape_msgs_genlisp)
add_dependencies(shape_msgs_genlisp shape_msgs_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS shape_msgs_generate_messages_lisp)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(shape_msgs
  "/home/pls/ydlidar_ws/src/ros/common_msgs/shape_msgs/msg/Mesh.msg"
  "${MSG_I_FLAGS}"
  "/home/pls/ydlidar_ws/src/ros/common_msgs/shape_msgs/msg/MeshTriangle.msg;/home/pls/ydlidar_ws/src/ros/common_msgs/geometry_msgs/msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/shape_msgs
)
_generate_msg_py(shape_msgs
  "/home/pls/ydlidar_ws/src/ros/common_msgs/shape_msgs/msg/MeshTriangle.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/shape_msgs
)
_generate_msg_py(shape_msgs
  "/home/pls/ydlidar_ws/src/ros/common_msgs/shape_msgs/msg/Plane.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/shape_msgs
)
_generate_msg_py(shape_msgs
  "/home/pls/ydlidar_ws/src/ros/common_msgs/shape_msgs/msg/SolidPrimitive.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/shape_msgs
)

### Generating Services

### Generating Module File
_generate_module_py(shape_msgs
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/shape_msgs
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(shape_msgs_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(shape_msgs_generate_messages shape_msgs_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/pls/ydlidar_ws/src/ros/common_msgs/shape_msgs/msg/Mesh.msg" NAME_WE)
add_dependencies(shape_msgs_generate_messages_py _shape_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pls/ydlidar_ws/src/ros/common_msgs/shape_msgs/msg/MeshTriangle.msg" NAME_WE)
add_dependencies(shape_msgs_generate_messages_py _shape_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pls/ydlidar_ws/src/ros/common_msgs/shape_msgs/msg/Plane.msg" NAME_WE)
add_dependencies(shape_msgs_generate_messages_py _shape_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pls/ydlidar_ws/src/ros/common_msgs/shape_msgs/msg/SolidPrimitive.msg" NAME_WE)
add_dependencies(shape_msgs_generate_messages_py _shape_msgs_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(shape_msgs_genpy)
add_dependencies(shape_msgs_genpy shape_msgs_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS shape_msgs_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/shape_msgs)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/shape_msgs
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
if(TARGET geometry_msgs_generate_messages_cpp)
  add_dependencies(shape_msgs_generate_messages_cpp geometry_msgs_generate_messages_cpp)
endif()
if(TARGET std_msgs_generate_messages_cpp)
  add_dependencies(shape_msgs_generate_messages_cpp std_msgs_generate_messages_cpp)
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/shape_msgs)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/shape_msgs
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
if(TARGET geometry_msgs_generate_messages_lisp)
  add_dependencies(shape_msgs_generate_messages_lisp geometry_msgs_generate_messages_lisp)
endif()
if(TARGET std_msgs_generate_messages_lisp)
  add_dependencies(shape_msgs_generate_messages_lisp std_msgs_generate_messages_lisp)
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/shape_msgs)
  install(CODE "execute_process(COMMAND \"/usr/bin/python3\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/shape_msgs\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/shape_msgs
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
if(TARGET geometry_msgs_generate_messages_py)
  add_dependencies(shape_msgs_generate_messages_py geometry_msgs_generate_messages_py)
endif()
if(TARGET std_msgs_generate_messages_py)
  add_dependencies(shape_msgs_generate_messages_py std_msgs_generate_messages_py)
endif()
