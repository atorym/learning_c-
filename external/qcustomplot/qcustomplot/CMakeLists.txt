set(name ${PROJECT_NAME})


add_library(${name}
  qcustomplot.h src/qcustomplot.cpp
  )

target_link_libraries(${name} PRIVATE
  Qt${QtVersion}::Widgets
  Qt${QtVersion}::PrintSupport
  )

target_include_directories(${name}
  PUBLIC
  "${PROJECT_SOURCE_DIR}"
  PRIVATE
  "${CMAKE_CURRENT_SOURCE_DIR}"
  )

target_compile_definitions(${name} PRIVATE
  QT_USE_QSTRINGBUILDER
  )

set_target_properties(${name} PROPERTIES
  AUTOMOC ON
  $<$<OR:$<CONFIG:Release>,$<CONFIG:MinSizeRel>>:INTERPROCEDURAL_OPTIMIZATION ON>
  )