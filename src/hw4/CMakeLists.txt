add_library(graphLib avl.c)

add_executable(graph main.c)

target_link_libraries(graph PRIVATE graphLib)
