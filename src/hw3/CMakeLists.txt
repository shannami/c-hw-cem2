add_library(avlLib avl.c)

add_executable(aerosoft main.c)

target_link_libraries(aerosoft PRIVATE avlLib)
