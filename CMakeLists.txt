cmake_minimum_required(VERSION 3.20.2)
project(
        asteroids
        VERSION 0.0.1
        LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG")

include_directories(include)

add_subdirectory(src)
add_subdirectory(tests)

add_subdirectory(libs/glad)
add_subdirectory(libs/linmath)

add_subdirectory(submodules/glfw)
add_subdirectory(submodules/googletest)
