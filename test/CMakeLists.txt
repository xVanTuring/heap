add_executable(TestHeap main.c)

include_directories(../src)
target_link_libraries(TestHeap LibHeap)
set_property(TARGET TestHeap PROPERTY C_STANDARD 11)