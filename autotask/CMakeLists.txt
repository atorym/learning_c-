add_library(autotask_sol)
target_link_extra_lib(autotask_sol)
target_pch(autotask_sol)

add_executable(autotask service/helper.hpp)
target_link_libraries(autotask
  autotask_sol
  gtest_main
  gmock
  )
target_include_directories(autotask PRIVATE .)


function(asm_task name)
  string(REPLACE . _ name ${name})
  set(name at_${name})

  function(task_config_file file to)
    get_filename_component(to ${to} REALPATH NAME)
    if(NOT EXISTS "${to}")
      set(task_id ${name})
      set(task_namespace ${task_id})
      set(task_include_dir ${task_id})
      configure_file(service/configs/${file}.in "${to}")
    endif()
  endfunction()

  set(task_dir volume/${name})
  function(task_config_file_solution file dir)
    set(to ${task_dir}/${dir}/${file})
    task_config_file(${file} ${to})
    target_sources(autotask_sol PRIVATE ${to})
  endfunction()

  function(task_config_file_solution_header file)
    set(header_dir include/${name})
    task_config_file_solution(${file} ${header_dir})
    target_include_directories(autotask_sol PUBLIC ${task_dir}/include)
  endfunction()

  function(task_config_file_solution_source file)
    task_config_file_solution(${file} .)
  endfunction()

  function(task_config_file_solution_test file)
    set(to ${task_dir}/${file})
    task_config_file(${file} ${to})
    target_sources(autotask PRIVATE ${to})
  endfunction()

  task_config_file_solution_header(solution.hpp)
  task_config_file_solution_source(solution.cpp)
  task_config_file_solution_test(test.cpp)
endfunction()


asm_task(2.1)
asm_task(2.4)
