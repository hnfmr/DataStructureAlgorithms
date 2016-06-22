cmake_minimum_required(VERSION 3.2)

project(AlgorithmsOnGraphs)

if (UNIX)
    set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
    set(CMAKE_CXX_FLAGS "-Wall -pipe -O2 -std=c++14")
endif(UNIX)

add_subdirectory("reachability")
add_subdirectory("connected_components")
add_subdirectory("acyclicity")
add_subdirectory("strongly_connected")
add_subdirectory("toposort")
