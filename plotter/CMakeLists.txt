set(target ${PROJECT_NAME})


add_subdirectory(core)


add_executable(${target}
  rc/rc.qrc
  src/main.cpp
  src/metatypes.cpp
  MainWindow.hpp src/MainWindow.cpp
  LabelAspectRatioPixmap.hpp src/LabelAspectRatioPixmap.cpp
)

target_link_libraries(${target} PRIVATE
  range-v3::range-v3
  Qt5::Widgets
  qcustomplot
  ${PROJECT_NAME}_core
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

if(WIN32)
  add_custom_command(TARGET ${target} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy -t $<TARGET_FILE_DIR:${target}> $<TARGET_RUNTIME_DLLS:${target}>
    COMMAND_EXPAND_LISTS
  )
  find_path(plugins_dir platforms
    HINTS "${Qt5_ROOT_DIR}"
    PATH_SUFFIXES plugins
    NO_CMAKE_SYSTEM_PATH
    NO_DEFAULT_PATH
    REQUIRED
  )
  file(GLOB plugins "${plugins_dir}/platforms/*")
  foreach(file IN LISTS plugins)
    get_filename_component(file_name "${file}" NAME)
    add_custom_command(TARGET ${target} POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy "${file}" "${CMAKE_CURRENT_BINARY_DIR}/plugins/platforms/${file_name}"
      COMMAND_EXPAND_LISTS
    )
  endforeach()
endif()

if(${${PROJECT_NAME}_UPPER}_USE_PCH OR ("${CMAKE_BUILD_TYPE}" STREQUAL "Debug" AND PROJECT_IS_TOP_LEVEL))
  target_precompile_headers(${target} PRIVATE
    "<range/v3/all.hpp>"
  )
endif()

if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug" AND PROJECT_IS_TOP_LEVEL)
  target_precompile_headers(${target} PRIVATE
    "<QDebug>"
  )
endif()
