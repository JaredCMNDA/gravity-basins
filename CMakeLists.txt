cmake_minimum_required(VERSION 3.10)
project(gravity-basins)

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
add_executable(gravity-basins main.cpp
        src/simulation.cpp
        src/simulation.h
        src/rendering.cpp
        src/rendering.h
        src/body.cpp
        src/body.h)
target_link_libraries(gravity-basins PRIVATE raylib)

