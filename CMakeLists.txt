cmake_minimum_required(VERSION 2.6)

set(RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(RUNTIME_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

message(${LIBRARY_OUTPUT_DIRECTORY})
message(${RUNTIME_OUTPUT_DIRECTORY})

project(poker)
ENABLE_TESTING()

find_package(Boost REQUIRED)
find_package(Qt4 REQUIRED)

set(MY_INCLUDE_DIRS ${Boost_INCLUDE_DIRS})

set (CMAKE_CXX_FLAGS "-g")

set(LANGUAGES
  nl_BE
)

set(TRANSLATION_DIR ${PROJECT_SOURCE_DIR}/translation)
add_custom_target(update_translations)

add_subdirectory(src)


