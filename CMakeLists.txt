cmake_minimum_required(VERSION 3.21)
project(pswgen LANGUAGES CXX VERSION 0.1)
set(CMAKE_CXX_STANDARD 20)


string(TOUPPER ${PROJECT_NAME} ${PROJECT_NAME}_UPPER )
set(${${PROJECT_NAME}_UPPER}_USE_PCH OFF CACHE BOOL "")


set(Qt5Libs Core Widgets)
find_package(Qt5 COMPONENTS ${Qt5Libs} REQUIRED)
file(REAL_PATH "${Qt5_DIR}/../../../" Qt5_ROOT_DIR) # TODO not working in linux

add_subdirectory(external/range-v3)
add_subdirectory(external/qcustomplot)


add_subdirectory(pswgen)
