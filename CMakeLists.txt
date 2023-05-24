cmake_minimum_required(VERSION 3.16.3)
project(learning_cpp CXX)
set(CMAKE_CXX_STANDARD 20)

add_subdirectory("${PROJECT_SOURCE_DIR}/external/gtest")

add_subdirectory(volume)