cmake_minimum_required(VERSION 3.16.3)
project(test_and_do)
set(CMAKE_CXX_STANDARD 20)


set(LIBS)

add_executable(test_and_do main.cpp)
target_link_libraries(test_and_do ${LIBS})