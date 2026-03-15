add_library(csvprinterLib csvPrinter.c)

add_executable(csvprinter main.c)

target_link_libraries(csvprinter PRIVATE csvprinterLib)
