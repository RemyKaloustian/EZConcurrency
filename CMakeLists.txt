cmake_minimum_required(VERSION 3.6)
project(EZConcurrency)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")



set(SOURCE_FILES
    inc/elements.h
    inc/launcher_version.h
    inc/movement.h
    inc/threading_part.h
    src/elements.c
    src/launcher_version.c
    src/main.c
    src/movement.c
    src/threading_part.c
        src/multiple_threads.c
        inc/multiple_threads.h
        src/designer.c
        inc/designer.h
        src/movement_sem.c
        inc/movement_sem.h)

add_executable(EZConcurrency ${SOURCE_FILES})
set(THREADS_PREFER_PTHREAD_FLAG ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -lpthread -O3")
find_package(Threads REQUIRED)
target_link_libraries (EZConcurrency m)
target_link_libraries(EZConcurrency Threads::Threads)

