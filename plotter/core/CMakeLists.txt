set(target ${PROJECT_NAME}_core)


add_library(${target} INTERFACE
  finally.hpp
  Singleton.hpp
  )
