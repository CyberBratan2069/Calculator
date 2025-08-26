cmake_minimum_required(VERSION 3.10)
project(RaylibProjekt C)

set(CMAKE_C_STANDARD 99)

find_package(raylib 5.0 REQUIRED) # sucht nach raylib

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

include_directories(${CMAKE_SOURCE_DIR}/lib/unity)
add_executable(UnityTests
        tests/UnityTests.c
        src/calc.c
        lib/Unity/src/unity.c
)

target_link_libraries(main raylib)