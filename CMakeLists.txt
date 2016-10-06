cmake_minimum_required(VERSION 3.6)
project(EZConcurrency)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")



set(SOURCE_FILES
    inc/elements.h
    inc/launcher_version.h
    inc/movement.h
    inc/threading_part.h
    src/determinism_choice.c
    src/elements.c
    src/launcher_version.c
    src/main.c
    src/movement.c
    src/threading_part.c
    )

add_executable(EZConcurrency ${SOURCE_FILES})
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
#target_link_libraries (EZConcurrency MathFunction)
target_link_libraries(EZConcurrency Threads::Threads)
