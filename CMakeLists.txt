cmake_minimum_required(VERSION 3.22)
project(octlib)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

include_directories(PUBLIC "include/common")
include_directories(PUBLIC "include/data_structures")

add_executable(test_static_range_query.out test/static_range_query.cpp)
add_executable(test_static_range_query_deep.out test/static_range_query_deep.cpp)
add_executable(test_vector_dimension.out test/vector_dimension.cpp)
