add_library(service_shared INTERFACE
  include/service_shared/helper.hpp
  )
target_include_directories(service_shared INTERFACE
  include
  )