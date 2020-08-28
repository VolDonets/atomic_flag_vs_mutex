cmake_minimum_required(VERSION 3.17)
project(atomic_flag_vs_mutes)

set(CMAKE_CXX_STANDARD 20)

add_executable(atomic_flag_test atomic_main.cpp)
add_executable(atomic_var_test atomic_var_test.cpp)
add_executable(mutex_test mutex_main.cpp )

target_link_libraries(atomic_flag_test pthread z)
target_link_libraries(mutex_test pthread z)
target_link_libraries(atomic_var_test pthread z)