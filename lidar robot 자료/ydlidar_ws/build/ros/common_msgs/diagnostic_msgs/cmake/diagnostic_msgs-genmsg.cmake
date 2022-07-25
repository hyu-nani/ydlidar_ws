# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "diagnostic_msgs: 3 messages, 2 services")

set(MSG_I_FLAGS "-Idiagnostic_msgs:/home/pls/ydlidar_ws/src/ros/common_msgs/diagnostic_msgs/msg;-Istd_msgs:/usr/share/std_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(genlisp REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(diagnostic_msgs_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/pls/ydlidar_ws/src/ros/common_msgs/diagnostic_msgs/msg/DiagnosticArray.msg" NAME_WE)
add_custom_target(_diagnostic_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "diagnostic_msgs" "/home/pls/ydlidar_ws/src/ros/common_msgs/diagnostic_msgs/msg/DiagnosticArray.msg" "diagnostic_msgs/DiagnosticStatus:diagnostic_msgs/KeyValue:std_msgs/Header"
)

get_filename_component(_filename "/home/pls/ydlidar_ws/src/ros/common_msgs/diagnostic_msgs/msg/DiagnosticStatus.msg" NAME_WE)
add_custom_target(_diagnostic_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "diagnostic_msgs" "/home/pls/ydlidar_ws/src/ros/common_msgs/diagnostic_msgs/msg/DiagnosticStatus.msg" "diagnostic_msgs/KeyValue"
)

get_filename_component(_filename "/home/pls/ydlidar_ws/src/ros/common_msgs/diagnostic_msgs/msg/KeyValue.msg" NAME_WE)
add_custom_target(_diagnostic_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "diagnostic_msgs" "/home/pls/ydlidar_ws/src/ros/common_msgs/diagnostic_msgs/msg/KeyValue.msg" ""
)

get_filename_component(_filename "/home/pls/ydlidar_ws/src/ros/common_msgs/diagnostic_msgs/srv/AddDiagnostics.srv" NAME_WE)
add_custom_target(_diagnostic_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "diagnostic_msgs" "/home/pls/ydlidar_ws/src/ros/common_msgs/diagnostic_msgs/srv/AddDiagnostics.srv" ""
)

get_filename_component(_filename "/home/pls/ydlidar_ws/src/ros/common_msgs/diagnostic_msgs/srv/SelfTest.srv" NAME_WE)
add_custom_target(_diagnostic_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "diagnostic_msgs" "/home/pls/ydlidar_ws/src/ros/common_msgs/diagnostic_msgs/srv/SelfTest.srv" "diagnostic_msgs/DiagnosticStatus:diagnostic_msgs/KeyValue"
)

#
#  langs = gencpp;genlisp;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(diagnostic_msgs
  "/home/pls/ydlidar_ws/src/ros/common_msgs/diagnostic_msgs/msg/DiagnosticArray.msg"
  "${MSG_I_FLAGS}"
  "/home/pls/ydlidar_ws/src/ros/common_msgs/diagnostic_msgs/msg/DiagnosticStatus.msg;/home/pls/ydlidar_ws/src/ros/common_msgs/diagnostic_msgs/msg/KeyValue.msg;/usr/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/diagnostic_msgs
)
_generate_msg_cpp(diagnostic_msgs
  "/home/pls/ydlidar_ws/src/ros/common_msgs/diagnostic_msgs/msg/DiagnosticStatus.msg"
  "${MSG_I_FLAGS}"
  "/home/pls/ydlidar_ws/src/ros/common_msgs/diagnostic_msgs/msg/KeyValue.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/diagnostic_msgs
)
_generate_msg_cpp(diagnostic_msgs
  "/home/pls/ydlidar_ws/src/ros/common_msgs/diagnostic_msgs/msg/KeyValue.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/diagnostic_msgs
)

### Generating Services
_generate_srv_cpp(diagnostic_msgs
  "/home/pls/ydlidar_ws/src/ros/common_msgs/diagnostic_msgs/srv/AddDiagnostics.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/diagnostic_msgs
)
_generate_srv_cpp(diagnostic_msgs
  "/home/pls/ydlidar_ws/src/ros/common_msgs/diagnostic_msgs/srv/SelfTest.srv"
  "${MSG_I_FLAGS}"
  "/home/pls/ydlidar_ws/src/ros/common_msgs/diagnostic_msgs/msg/DiagnosticStatus.msg;/home/pls/ydlidar_ws/src/ros/common_msgs/diagnostic_msgs/msg/KeyValue.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/diagnostic_msgs
)

### Generating Module File
_generate_module_cpp(diagnostic_msgs
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/diagnostic_msgs
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(diagnostic_msgs_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(diagnostic_msgs_generate_messages diagnostic_msgs_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/pls/ydlidar_ws/src/ros/common_msgs/diagnostic_msgs/msg/DiagnosticArray.msg" NAME_WE)
add_dependencies(diagnostic_msgs_generate_messages_cpp _diagnostic_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pls/ydlidar_ws/src/ros/common_msgs/diagnostic_msgs/msg/DiagnosticStatus.msg" NAME_WE)
add_dependencies(diagnostic_msgs_generate_messages_cpp _diagnostic_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pls/ydlidar_ws/src/ros/common_msgs/diagnostic_msgs/msg/KeyValue.msg" NAME_WE)
add_dependencies(diagnostic_msgs_generate_messages_cpp _diagnostic_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pls/ydlidar_ws/src/ros/common_msgs/diagnostic_msgs/srv/AddDiagnostics.srv" NAME_WE)
add_dependencies(diagnostic_msgs_generate_messages_cpp _diagnostic_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pls/ydlidar_ws/src/ros/common_msgs/diagnostic_msgs/srv/SelfTest.srv" NAME_WE)
add_dependencies(diagnostic_msgs_generate_messages_cpp _diagnostic_msgs_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(diagnostic_msgs_gencpp)
add_dependencies(diagnostic_msgs_gencpp diagnostic_msgs_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS diagnostic_msgs_generate_messages_cpp)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(diagnostic_msgs
  "/home/pls/ydlidar_ws/src/ros/common_msgs/diagnostic_msgs/msg/DiagnosticArray.msg"
  "${MSG_I_FLAGS}"
  "/home/pls/ydlidar_ws/src/ros/common_msgs/diagnostic_msgs/msg/DiagnosticStatus.msg;/home/pls/ydlidar_ws/src/ros/common_msgs/diagnostic_msgs/msg/KeyValue.msg;/usr/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/diagnostic_msgs
)
_generate_msg_lisp(diagnostic_msgs
  "/home/pls/ydlidar_ws/src/ros/common_msgs/diagnostic_msgs/msg/DiagnosticStatus.msg"
  "${MSG_I_FLAGS}"
  "/home/pls/ydlidar_ws/src/ros/common_msgs/diagnostic_msgs/msg/KeyValue.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/diagnostic_msgs
)
_generate_msg_lisp(diagnostic_msgs
  "/home/pls/ydlidar_ws/src/ros/common_msgs/diagnostic_msgs/msg/KeyValue.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/diagnostic_msgs
)

### Generating Services
_generate_srv_lisp(diagnostic_msgs
  "/home/pls/ydlidar_ws/src/ros/common_msgs/diagnostic_msgs/srv/AddDiagnostics.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/diagnostic_msgs
)
_generate_srv_lisp(diagnostic_msgs
  "/home/pls/ydlidar_ws/src/ros/common_msgs/diagnostic_msgs/srv/SelfTest.srv"
  "${MSG_I_FLAGS}"
  "/home/pls/ydlidar_ws/src/ros/common_msgs/diagnostic_msgs/msg/DiagnosticStatus.msg;/home/pls/ydlidar_ws/src/ros/common_msgs/diagnostic_msgs/msg/KeyValue.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/diagnostic_msgs
)

### Generating Module File
_generate_module_lisp(diagnostic_msgs
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/diagnostic_msgs
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(diagnostic_msgs_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(diagnostic_msgs_generate_messages diagnostic_msgs_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/pls/ydlidar_ws/src/ros/common_msgs/diagnostic_msgs/msg/DiagnosticArray.msg" NAME_WE)
add_dependencies(diagnostic_msgs_generate_messages_lisp _diagnostic_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pls/ydlidar_ws/src/ros/common_msgs/diagnostic_msgs/msg/DiagnosticStatus.msg" NAME_WE)
add_dependencies(diagnostic_msgs_generate_messages_lisp _diagnostic_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pls/ydlidar_ws/src/ros/common_msgs/diagnostic_msgs/msg/KeyValue.msg" NAME_WE)
add_dependencies(diagnostic_msgs_generate_messages_lisp _diagnostic_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pls/ydlidar_ws/src/ros/common_msgs/diagnostic_msgs/srv/AddDiagnostics.srv" NAME_WE)
add_dependencies(diagnostic_msgs_generate_messages_lisp _diagnostic_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pls/ydlidar_ws/src/ros/common_msgs/diagnostic_msgs/srv/SelfTest.srv" NAME_WE)
add_dependencies(diagnostic_msgs_generate_messages_lisp _diagnostic_msgs_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(diagnostic_msgs_genlisp)
add_dependencies(diagnostic_msgs_genlisp diagnostic_msgs_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS diagnostic_msgs_generate_messages_lisp)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(diagnostic_msgs
  "/home/pls/ydlidar_ws/src/ros/common_msgs/diagnostic_msgs/msg/DiagnosticArray.msg"
  "${MSG_I_FLAGS}"
  "/home/pls/ydlidar_ws/src/ros/common_msgs/diagnostic_msgs/msg/DiagnosticStatus.msg;/home/pls/ydlidar_ws/src/ros/common_msgs/diagnostic_msgs/msg/KeyValue.msg;/usr/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/diagnostic_msgs
)
_generate_msg_py(diagnostic_msgs
  "/home/pls/ydlidar_ws/src/ros/common_msgs/diagnostic_msgs/msg/DiagnosticStatus.msg"
  "${MSG_I_FLAGS}"
  "/home/pls/ydlidar_ws/src/ros/common_msgs/diagnostic_msgs/msg/KeyValue.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/diagnostic_msgs
)
_generate_msg_py(diagnostic_msgs
  "/home/pls/ydlidar_ws/src/ros/common_msgs/diagnostic_msgs/msg/KeyValue.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/diagnostic_msgs
)

### Generating Services
_generate_srv_py(diagnostic_msgs
  "/home/pls/ydlidar_ws/src/ros/common_msgs/diagnostic_msgs/srv/AddDiagnostics.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/diagnostic_msgs
)
_generate_srv_py(diagnostic_msgs
  "/home/pls/ydlidar_ws/src/ros/common_msgs/diagnostic_msgs/srv/SelfTest.srv"
  "${MSG_I_FLAGS}"
  "/home/pls/ydlidar_ws/src/ros/common_msgs/diagnostic_msgs/msg/DiagnosticStatus.msg;/home/pls/ydlidar_ws/src/ros/common_msgs/diagnostic_msgs/msg/KeyValue.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/diagnostic_msgs
)

### Generating Module File
_generate_module_py(diagnostic_msgs
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/diagnostic_msgs
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(diagnostic_msgs_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(diagnostic_msgs_generate_messages diagnostic_msgs_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/pls/ydlidar_ws/src/ros/common_msgs/diagnostic_msgs/msg/DiagnosticArray.msg" NAME_WE)
add_dependencies(diagnostic_msgs_generate_messages_py _diagnostic_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pls/ydlidar_ws/src/ros/common_msgs/diagnostic_msgs/msg/DiagnosticStatus.msg" NAME_WE)
add_dependencies(diagnostic_msgs_generate_messages_py _diagnostic_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pls/ydlidar_ws/src/ros/common_msgs/diagnostic_msgs/msg/KeyValue.msg" NAME_WE)
add_dependencies(diagnostic_msgs_generate_messages_py _diagnostic_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pls/ydlidar_ws/src/ros/common_msgs/diagnostic_msgs/srv/AddDiagnostics.srv" NAME_WE)
add_dependencies(diagnostic_msgs_generate_messages_py _diagnostic_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/pls/ydlidar_ws/src/ros/common_msgs/diagnostic_msgs/srv/SelfTest.srv" NAME_WE)
add_dependencies(diagnostic_msgs_generate_messages_py _diagnostic_msgs_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(diagnostic_msgs_genpy)
add_dependencies(diagnostic_msgs_genpy diagnostic_msgs_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS diagnostic_msgs_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/diagnostic_msgs)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/diagnostic_msgs
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_cpp)
  add_dependencies(diagnostic_msgs_generate_messages_cpp std_msgs_generate_messages_cpp)
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/diagnostic_msgs)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/diagnostic_msgs
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_lisp)
  add_dependencies(diagnostic_msgs_generate_messages_lisp std_msgs_generate_messages_lisp)
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/diagnostic_msgs)
  install(CODE "execute_process(COMMAND \"/usr/bin/python3\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/diagnostic_msgs\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/diagnostic_msgs
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_py)
  add_dependencies(diagnostic_msgs_generate_messages_py std_msgs_generate_messages_py)
endif()
