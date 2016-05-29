cmake_minimum_required(VERSION 3.2)

project(DataStructures)

if (UNIX)
    set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
    set(CMAKE_CXX_FLAGS "-Wall -pipe -O2 -std=c++14")
endif(UNIX)

add_subdirectory("Starters\ PA1/check_brackets_in_code")
add_subdirectory("Starters\ PA1/network_packet_processing_simulation")
add_subdirectory("Starters\ PA1/tree_height")

add_subdirectory("Starters\ PA2/job_queue")
add_subdirectory("Starters\ PA2/make_heap")
add_subdirectory("Starters\ PA2/merging_tables")

add_subdirectory("Starters\ PA3/hash_chains")
add_subdirectory("Starters\ PA3/hash_substring")
add_subdirectory("Starters\ PA3/phone_book")

add_subdirectory("Starters\ PA4/rope")
add_subdirectory("Starters\ PA4/set_range_sum")
add_subdirectory("Starters\ PA4/tree_orders")
