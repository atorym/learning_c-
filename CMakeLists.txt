cmake_minimum_required(VERSION 3.16.3)
project(test_and_do)
set(CMAKE_CXX_STANDARD 20)


add_subdirectory(range-v3)
#add_subdirectory(fmt)

set(LIBS range-v3::range-v3
#fmt::fmt
)

set(QT5_LIBS)
set(QT5_LIBS_NAME Core Widgets)
find_package(Qt5 COMPONENTS ${QT5_LIBS_NAME})
if(Qt5_FOUND)
  foreach(lib ${QT5_LIBS_NAME})
    list(APPEND LIBS Qt5::${lib})
  endforeach()
endif()

find_package(Boost)
if(Boost_FOUND)
  list(APPEND LIBS Boost::boost)
endif()

add_executable(test_and_do main.cpp)
target_link_libraries(test_and_do ${LIBS})
if(Qt5_FOUND)
  set_target_properties(test_and_do PROPERTIES
    AUTOMOC ON
    AUTOUIC ON
    INCLUDE_CURRENT_DIR ON
    AUTOUIC_SEARCH_PATHS ${PROJECT_SOURCE_DIR}
    )
endif()
