add_executable(TestHeap main.c)

include_directories(../src)
target_link_libraries(TestHeap LibHeap)