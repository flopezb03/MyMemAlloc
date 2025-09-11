cmake_minimum_required(VERSION 3.10)
project(MyMemAlloc C)

add_compile_options(-Wall -Wextra -fPIC)

include_directories(include)    

add_library(my_mem_alloc SHARED src/my_mem_alloc.c)

set_target_properties(my_mem_alloc PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib
)