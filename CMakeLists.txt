cmake_minimum_required(VERSION 3.17)
project(zappy LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED true)

add_compile_options(
    "-Wall" "-Wextra" "-Werror" "-pedantic" "-Wpointer-arith" "-fpic"
)

option(TESTING OFF)
if (TESTING)
    add_compile_options("--coverage" "-fprofile-arcs" "-ftest-coverage")
    add_link_options("--coverage" "-fprofile-arcs" "-ftest-coverage")
    add_subdirectory(tests)
endif()
