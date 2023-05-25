function(asm_task name)
  string(REPLACE . _ name ${name})

  set(sol at_${name}_sol)
  add_library(${sol} STATIC)
  target_link_extra_lib(${sol})
  target_pch(${sol})

  set(test at_${name})
  add_executable(${test} service/helper.hpp)
  target_link_libraries(${test}
    ${sol}
    gtest_main
    gmock
    )
  target_include_directories(${test} PRIVATE .)

  function(task_config_file file to)
    get_filename_component(to ${to} REALPATH NAME)
    if(NOT EXISTS "${to}")
      set(task_include_dir ${name})
      string(TOLOWER ${name} task_namespace)
      set(task_id ${task_namespace})
      configure_file(service/configs/${file}.in "${to}")
    endif()
  endfunction()

  set(task_dir volume/${name})
  function(task_config_file_solution file dir)
    set(to ${task_dir}/${dir}/${file})
    task_config_file(${file} ${to})
    target_sources(${sol} PRIVATE ${to})
  endfunction()

  function(task_config_file_solution_header file)
    set(header_dir include/${name})
    task_config_file_solution(${file} ${header_dir})
    target_include_directories(${sol} PUBLIC ${task_dir}/include)
  endfunction()

  function(task_config_file_solution_source file)
    task_config_file_solution(${file} .)
  endfunction()

  function(task_config_file_solution_test file)
    set(to ${task_dir}/${file})
    task_config_file(${file} ${to})
    target_sources(${test} PRIVATE ${to})
  endfunction()

  task_config_file_solution_header(solution.hpp)
  task_config_file_solution_source(solution.cpp)
  task_config_file_solution_test(test.cpp)
endfunction()


#asm_task()
