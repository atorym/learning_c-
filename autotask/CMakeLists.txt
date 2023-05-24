add_executable(autotask)
target_link_libraries(autotask
  gtest_main
  gmock
  )


file(GLOB config_files_full_path service/*)
foreach(i ${config_files_full_path})
  get_filename_component(i "${i}" NAME)
  list(APPEND config_files ${i})
endforeach()


function(task_init name)
  get_filename_component(task_dir "volume/${name}" REALPATH BASE_DIR)
  foreach(i ${config_files})
    set(intended_path "${task_dir}/${i}")
    if(NOT EXISTS "${intended_path}")
      set(task_namespace ${name})
      set(task_id ${task_namespace})
      configure_file(service/${i} "${intended_path}")
    endif()
  endforeach()
endfunction()


function(asm_task name)
  task_init(${name})
  set(curr volume/${name})
  file(GLOB files ${curr}/*)
  target_sources(autotask PRIVATE "${files}")
  target_include_directories(autotask PRIVATE ${curr})
endfunction()


asm_task(_2_1)
