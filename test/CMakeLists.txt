add_executable(TestHeap main.cc)

include_directories(../src)
target_link_libraries(TestHeap LibHeap)
set_property(TARGET TestHeap PROPERTY CXX_STANDARD 11)