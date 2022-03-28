set(BINARY ${CMAKE_PROJECT_NAME})

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.h *.cpp)

set(SOURCES ${SOURCES})

add_executable(${BINARY} ${SOURCES})
target_compile_options(${BINARY} PRIVATE
        -Wall
        -Werror
        -Wextra
        -Wpedantic
        $<$<CONFIG:Debug>:-O0>
        $<$<CONFIG:Release>:-O3>
        )
target_link_libraries(${BINARY} PUBLIC dl glad glfw linmath)

add_library(${BINARY}_lib STATIC ${SOURCES})
target_compile_options(${BINARY}_lib PRIVATE
        -Wall
        -Werror
        -Wextra
        -Wpedantic
        $<$<CONFIG:Debug>:-O0>
        $<$<CONFIG:Release>:-O3>
        )
target_link_libraries(${BINARY}_lib PUBLIC dl glad glfw linmath)
