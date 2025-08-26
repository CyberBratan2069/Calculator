cmake_minimum_required(VERSION 3.10)
project(RayLibProjekt C)

set(CMAKE_C_STANDARD 99)

# Raylib direkt aus dem Projekt einbinden
find_package(raylib 5.0 REQUIRED)

add_executable(main
        src/main.c
        src/ui.c
        src/calc.c
        src/button.c
        src/ui.h
        src/button.h
        src/calc.h
)

target_link_libraries(main raylib)

# Unity Tests

