set(target ${PROJECT_NAME}_core)


add_library(${target}
  finally.hpp
  Singleton.hpp
  NetworkAccess.hpp src/NetworkAccess.cpp
  )

target_link_libraries(${target} PRIVATE
  Qt5::Network
  )

target_include_directories(${target} PRIVATE
  "${PROJECT_SOURCE_DIR}"
  )
