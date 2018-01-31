# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "pre_processer: 1 messages, 0 services")

set(MSG_I_FLAGS "-Ipre_processer:/home/hntea/RobotWorkSpace/SpeechSystem/speech_system/src/pre_processer/msg;-Istd_msgs:/opt/ros/indigo/share/std_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(genlisp REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(pre_processer_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/hntea/RobotWorkSpace/SpeechSystem/speech_system/src/pre_processer/msg/OneChannelDataset.msg" NAME_WE)
add_custom_target(_pre_processer_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "pre_processer" "/home/hntea/RobotWorkSpace/SpeechSystem/speech_system/src/pre_processer/msg/OneChannelDataset.msg" ""
)

#
#  langs = gencpp;genlisp;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(pre_processer
  "/home/hntea/RobotWorkSpace/SpeechSystem/speech_system/src/pre_processer/msg/OneChannelDataset.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/pre_processer
)

### Generating Services

### Generating Module File
_generate_module_cpp(pre_processer
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/pre_processer
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(pre_processer_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(pre_processer_generate_messages pre_processer_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/hntea/RobotWorkSpace/SpeechSystem/speech_system/src/pre_processer/msg/OneChannelDataset.msg" NAME_WE)
add_dependencies(pre_processer_generate_messages_cpp _pre_processer_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(pre_processer_gencpp)
add_dependencies(pre_processer_gencpp pre_processer_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS pre_processer_generate_messages_cpp)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(pre_processer
  "/home/hntea/RobotWorkSpace/SpeechSystem/speech_system/src/pre_processer/msg/OneChannelDataset.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/pre_processer
)

### Generating Services

### Generating Module File
_generate_module_lisp(pre_processer
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/pre_processer
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(pre_processer_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(pre_processer_generate_messages pre_processer_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/hntea/RobotWorkSpace/SpeechSystem/speech_system/src/pre_processer/msg/OneChannelDataset.msg" NAME_WE)
add_dependencies(pre_processer_generate_messages_lisp _pre_processer_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(pre_processer_genlisp)
add_dependencies(pre_processer_genlisp pre_processer_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS pre_processer_generate_messages_lisp)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(pre_processer
  "/home/hntea/RobotWorkSpace/SpeechSystem/speech_system/src/pre_processer/msg/OneChannelDataset.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/pre_processer
)

### Generating Services

### Generating Module File
_generate_module_py(pre_processer
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/pre_processer
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(pre_processer_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(pre_processer_generate_messages pre_processer_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/hntea/RobotWorkSpace/SpeechSystem/speech_system/src/pre_processer/msg/OneChannelDataset.msg" NAME_WE)
add_dependencies(pre_processer_generate_messages_py _pre_processer_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(pre_processer_genpy)
add_dependencies(pre_processer_genpy pre_processer_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS pre_processer_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/pre_processer)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/pre_processer
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_cpp)
  add_dependencies(pre_processer_generate_messages_cpp std_msgs_generate_messages_cpp)
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/pre_processer)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/pre_processer
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_lisp)
  add_dependencies(pre_processer_generate_messages_lisp std_msgs_generate_messages_lisp)
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/pre_processer)
  install(CODE "execute_process(COMMAND \"/usr/bin/python\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/pre_processer\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/pre_processer
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_py)
  add_dependencies(pre_processer_generate_messages_py std_msgs_generate_messages_py)
endif()
