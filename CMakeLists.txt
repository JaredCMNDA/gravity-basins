cmake_minimum_required(VERSION 3.10)
project(orbital-mechanics)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

# raylib via fetch content
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG 5.5
)
FetchContent_MakeAvailable(raylib)

# add executable
add_executable(orbital-mechanics src/main.cpp
        src/core/shape.cpp
        src/core/shape.h
        src/core/body.cpp
        src/core/body.h
        src/core/simulation.cpp
        src/core/simulation.h
        src/physics/collisiondetector.cpp
        src/physics/collisiondetector.h
        src/physics/collisionresolver.cpp
        src/physics/collisionresolver.h
        src/input/app_state.cpp
        src/input/app_state.h
        src/input/draw_state.cpp
        src/input/draw_state.h
        src/input/simulation_state.cpp
        src/input/simulation_state.h)

target_link_libraries(orbital-mechanics PRIVATE raylib)

