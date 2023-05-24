add_executable(autotask)
target_link_libraries(autotask
  gtest_main
  gmock
  )


function(task_init_in name file)
  get_filename_component(file_path "volume/${name}/${file}" REALPATH BASE_DIR)
  if(NOT EXISTS "${file_path}")
    set(task_namespace "${name}")
    set(task_id "${task_namespace}")
    configure_file(service/${file}.in "${file_path}")
  endif()
endfunction()


function(asm_task name)
  task_init_in(${name} solution.cpp)
  task_init_in(${name} test.cpp)
  set(curr volume/${name})
  file(GLOB files ${curr}/*)
  target_sources(autotask PRIVATE "${files}")
endfunction()


asm_task(_2_1)
