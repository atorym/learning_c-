# https://stackoverflow.com/a/71169735
macro(subdirlist result curdir)
  set(${result} "")
  file(GLOB children ${curdir}/*) # This was changed
  foreach(child ${children})
    if(IS_DIRECTORY ${child}) # This was changed
      list(APPEND ${result} ${child})
    endif()
  endforeach()
endmacro()


function(asm_task dir)
  get_filename_component(name ${dir} NAME)
  file(GLOB files ${dir}/*)
  add_executable(${name}
    ${dir}/test.cpp
    ${dir}/solution.cpp
    ${files}
    )
  target_link_libraries(${name}
    gtest_main
    gmock
    )
endfunction()


subdirlist(subdir "${CMAKE_CURRENT_LIST_DIR}")
foreach(i ${subdir})
  asm_task(${i})
endforeach()