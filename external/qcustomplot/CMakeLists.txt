cmake_minimum_required(VERSION 3.0)
project(qcustomplot LANGUAGES CXX VERSION 2.1.1)


set(QtVersion 5 CACHE STRING "${PROJECT_NAME} qt version")


set(Qt5Libs Widgets PrintSupport)
#set(Qt6Libs ...)
find_package(Qt${QtVersion} COMPONENTS ${Qt${QtVersion}Libs} REQUIRED)


add_subdirectory(qcustomplot)
