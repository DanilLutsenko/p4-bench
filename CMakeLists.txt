cmake_minimum_required(VERSION 3.0.2 FATAL_ERROR)

add_executable(p4-bench src/bench.cpp src/cstring.cpp src/hash.cpp src/old_cstring.cpp)
target_compile_options(p4-bench PUBLIC "-O1")