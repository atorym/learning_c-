cmake_minimum_required(VERSION 3.21)
project(learning_autotask CXX)
set(CMAKE_CXX_STANDARD 20)


add_subdirectory(external/gtest)
add_subdirectory(external/fmt)
add_subdirectory(external/range-v3)

function(target_link_extra_lib target)
  target_link_libraries(${target} PUBLIC
    range-v3::range-v3
    fmt::fmt
    )
endfunction()

function(target_pch target)
  target_precompile_headers(${target} PUBLIC
    "<range/v3/all.hpp>"

    "<fmt/printf.h>"
    "<fmt/format.h>"

    "<algorithm>"
    "<any>"
    "<array>"
    "<atomic>"
    "<barrier>"
    "<cmath>"
    "<cassert>"
    "<bit>"
    "<bitset>"
    "<deque>"
    "<exception>"
    "<execution>"
    "<expected>"
    "<filesystem>"
    "<forward_list>"
    "<fstream>"
    "<functional>"
    "<future>"
    "<initializer_list>"
    "<iomanip>"
    "<ios>"
    "<iosfwd>"
    "<iostream>"
    "<istream>"
    "<iterator>"
    "<latch>"
    "<limits>"
    "<list>"
    "<locale>"
    "<map>"
    "<memory>"
    "<memory_resource>"
    "<mutex>"
    "<new>"
    "<numbers>"
    "<numeric>"
    "<optional>"
    "<ostream>"
    "<queue>"
    "<random>"
    "<ranges>"
    "<ratio>"
    "<regex>"
    "<scoped_allocator>"
    "<semaphore>"
    "<set>"
    "<shared_mutex>"
    "<source_location>"
    "<span>"
    "<spanstream>"
    "<sstream>"
    "<stack>"
    "<stacktrace>"
    "<stdexcept>"
    "<stop_token>"
    "<streambuf>"
    "<string>"
    "<string_view>"
    "<syncstream>"
    "<system_error>"
    "<thread>"
    "<tuple>"
    "<typeindex>"
    "<typeinfo>"
    "<type_traits>"
    "<unordered_map>"
    "<unordered_set>"
    "<utility>"
    "<valarray>"
    "<variant>"
    "<vector>"
    "<version>"
    )
endfunction()


add_subdirectory(autotask)
add_subdirectory(sandbox)
