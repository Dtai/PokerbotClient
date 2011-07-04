include(${PROJECT_SOURCE_DIR}/script/macro.txt)

# copy the proto-buf source directory to binary dir

SET(PROTOBUF_OUTPUT_DIR ${CMAKE_BINARY_DIR}/protobuf_source)

if(NOT IS_DIRECTORY ${PROTOBUF_OUTPUT_DIR})
  execute_process(COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/protobuf-source ${PROTOBUF_OUTPUT_DIR})
  execute_process(WORKING_DIRECTORY ${PROTOBUF_OUTPUT_DIR} COMMAND ${PROTOBUF_OUTPUT_DIR}/configure)
endif(NOT IS_DIRECTORY ${PROTOBUF_OUTPUT_DIR})

set(PROTOBUF_ROOT ${PROTOBUF_OUTPUT_DIR})

add_subdirectory(protobuf-cmake)

