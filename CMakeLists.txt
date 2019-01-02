cmake_minimum_required (VERSION 2.8)
 
project (HEAP)

add_library(Heap heap.c utils.c)

add_executable(Run main.c)

target_link_libraries(Run Heap)