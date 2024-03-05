cmake_minimum_required(VERSION 3.25)

project(RVC)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-deprecated-declarations")

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -O0")
elseif (CMAKE_BUILD_TYPE STREQUAL "DebugAddress")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -O0 -fsanitize=address")
elseif (CMAKE_BUILD_TYPE STREQUAL "DebugLeak")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -O0 -fsanitize=leak")
elseif (CMAKE_BUILD_TYPE STREQUAL "DebugMemory")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -O0 -fsanitize=memory")
elseif (CMAKE_BUILD_TYPE STREQUAL "Release")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3")
endif ()

set(SOURCE_FILES 
                src/main.c
                src/paths.h
                src/init.h src/init.c
                src/add.h src/add.c
                src/commit.h src/commit.c
                src/error_handling.h src/error_handling.c
                src/utils.h src/utils.c)

find_package(OpenSSL REQUIRED)
find_package(ZLIB REQUIRED)

add_executable(rvc ${SOURCE_FILES})
target_link_libraries(rvc OpenSSL::SSL ZLIB::ZLIB)