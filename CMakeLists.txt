project(RVC)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c17")

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0")
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
endif()

set(SOURCE_FILES 
                src/main.c
                src/init.h src/init.c)

add_executable(rvc ${SOURCE_FILES})