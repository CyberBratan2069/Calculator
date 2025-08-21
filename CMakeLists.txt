cmake_minimum_required(VERSION 3.10)
project(RaylibProjekt C)

set(CMAKE_C_STANDARD 99)

find_package(raylib 5.0 REQUIRED) # sucht nach raylib

add_executable(main main.c)

target_link_libraries(main raylib)

