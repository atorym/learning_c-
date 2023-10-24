cmake_minimum_required(VERSION 3.14)
project(pswgen LANGUAGES CXX VERSION 0.1)
set(CMAKE_CXX_STANDARD 20)


set(Qt5Libs Core Widgets)
find_package(Qt5 COMPONENTS ${Qt5Libs} REQUIRED)

add_subdirectory(external/range)
add_subdirectory(external/qcustomplot)


set(target ${PROJECT_NAME})

add_executable(${target}
  rc/rc.qrc
  src/main.cpp
  src/meta_types.cpp
  impl.hpp src/impl.cpp
  MainWindow.hpp src/MainWindow.cpp
  src/PresetBox.cpp PresetBox.hpp
  CapacityBox.hpp src/CapacityBox.cpp
  GenPage.hpp src/GenPage.cpp
  LabelAspectRatioPixmap.hpp src/LabelAspectRatioPixmap.cpp
  DistributionPage.hpp src/DistributionPage.cpp
  )

target_link_libraries(${target} PRIVATE
  range-v3::range-v3
  Qt5::Widgets
  qcustomplot
  )

target_include_directories(${target} PRIVATE
  "${PROJECT_SOURCE_DIR}"
  )

set_target_properties(${target} PROPERTIES
  AUTOMOC ON
  AUTOUIC ON
  AUTORCC ON
  INCLUDE_CURRENT_DIR ON
  AUTOUIC_SEARCH_PATHS ui
  $<$<OR:$<CONFIG:Release>,$<CONFIG:MinSizeRel>>:INTERPROCEDURAL_OPTIMIZATION ON>
  )

target_compile_definitions(${target} PRIVATE
  QT_USE_QSTRINGBUILDER
  )

target_compile_definitions(${target} PRIVATE
  PROJECT_NAME="${PROJECT_NAME}"
  PROJECT_VERSION="${PROJECT_VERSION}"
  )


  target_precompile_headers(${target} PRIVATE
    "<QDebug>"
    "<range/v3/all.hpp>"
    )
