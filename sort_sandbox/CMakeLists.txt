set(sub_name sandbox_sort)


function(src_cfg file to)
  get_filename_component(to ${to} REALPATH NAME)
  if(NOT EXISTS "${to}")
    configure_file(service/${file}.in "${to}")
  endif()
endfunction()


macro(add_sort name)
  string(REPLACE . _ name ${name})

  set(sol ${sub_name}_${name}_sol)
  add_library(${sol} STATIC
    include/sandbox_sort/defines.hpp
    )
  target_link_extra_lib(${sol})
  target_pch(${sol})
  target_include_directories(${sol} PUBLIC
    include
    )

  set(test ${sub_name}_${name})
  add_executable(${test}
    test.cpp
    )
  target_link_libraries(${test} PRIVATE
    ${sol}
    gtest_main
    gmock
    )
  target_include_directories(${test} PRIVATE .)

  set(sort_src volume/${name}.cpp)
  src_cfg(src.cpp ${sort_src})
  target_sources(${sol} PRIVATE ${sort_src})
endmacro()


add_sort(bubble)
