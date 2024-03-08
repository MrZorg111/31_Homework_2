cmake_minimum_required(VERSION 3.17)

add_executable(31_Homework_2 main.cpp ${MY_INCLUDE_DIR}/function.h)
target_include_directories(31_Homework_2 PUBLIC ${MY_INCLUDE_DIR})