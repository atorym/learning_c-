add_executable(autotask)
target_link_libraries(autotask
  gtest_main
  gmock
  )


function(tasasm_taskk_init name)
  string(REPLACE "." "_" name ${name})
  set(name "at_${name}")
#  target_include_directories(autotask PRIVATE ${curr})

  function(task_config_file file to)
    get_filename_component(to ${to} REALPATH NAME)
    if(NOT EXISTS "${to}")
      set(task_namespace ${name})
      set(task_id ${task_namespace})
      configure_file(service/configs/${file} "${to}")
    endif()
  endfunction()

  set(task_dir volume/${name})
  function(task_config_file_solution file)
    get_filename_component(file_wle ${file} NAME_WLE)
    task_config_file(${file} ${task_dir}/${file_wle})
  endfunction()

  function(task_config_file_solution_test file)
    get_filename_component(file_wle ${file} NAME_WLE)
    task_config_file(${file} tests/${file_wle})
  endfunction()

  task_config_file_solution(solution.hpp.in)
  task_config_file_solution(solution.cpp.in)
  task_config_file_solution_test(test.cpp.in)
endfunction()


asm_task(2.1)
#asm_task(2.4)
