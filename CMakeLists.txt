cmake_minimum_required(VERSION 3.12)
project(FdF C)

set(CMAKE_C_STANDARD 99)

AUX_SOURCE_DIRECTORY(Libft LIBA)

add_executable(FdF
        main.c
        ${LIBA}
        incl/fdf.h validation.c drawing.c function.c function1.c)

link_libraries(./libft/libft.a)