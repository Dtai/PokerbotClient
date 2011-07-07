cmake_minimum_required(VERSION 2.6)

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
