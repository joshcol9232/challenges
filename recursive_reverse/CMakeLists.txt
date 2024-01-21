cmake_minimum_required (VERSION 3.0)

# Below line is for using C++14 standard
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

project(recur_reverse)

add_executable(recur_reverse main.cpp)

# target_link_libraries(framework)
