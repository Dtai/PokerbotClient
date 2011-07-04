include_directories(${PROJECT_SOURCE_DIR}/src/lib ${MY_INCLUDE_DIRS})

add_executable(CreateTest createtest.cpp)

add_subdirectory(modelTest)
#add_subdirectory(parserTest)
add_subdirectory(viewTest)
add_subdirectory(qtSerializationTest)
