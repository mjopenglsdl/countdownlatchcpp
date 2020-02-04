cmake_minimum_required(VERSION 3.0.2)

project(coutdown_latch_test)

file(GLOB SRC_FILES "*.cpp")

add_executable(${PROJECT_NAME} ${SRC_FILES})  