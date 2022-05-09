cmake_minimum_required(VERSION 3.20)
set(namespace 
        "containers")
project("containers"
        DESCRIPTION "A dynamic container library"
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_BUILD_TYPE Debug)

if (NOT CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
        message(STATUS "This project has a top-level one called [${CMAKE_PROJECT_NAME}]")
else()
        message(STATUS "This project is a top-level one.")
endif()

add_library(${PROJECT_NAME} STATIC)
add_executable(${PROJECT_NAME}_test)

set(CXX_COMPILE_FLAGS)
list(APPEND CXX_COMPILE_FLAGS -std=c++20 -Wall -Wextra -pedantic -Wno-narrowing -Wno-sign-compare)

target_sources(${PROJECT_NAME}
        PRIVATE
                src/containers.cpp
)
target_sources(${PROJECT_NAME}_test
        PRIVATE
                test/testing.cpp)

target_include_directories(${PROJECT_NAME}
        PRIVATE SYSTEM
                # The library itself will look for internal headers here.
                ${CMAKE_CURRENT_SOURCE_DIR}/src
                ${CMAKE_CURRENT_SOURCE_DIR}/include
        PUBLIC
                # Top-level projects will look for public headers here.
                $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                # External projects will look for public headers here.
                $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)
target_include_directories(${PROJECT_NAME}_test
        PRIVATE SYSTEM
                ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_compile_options(${PROJECT_NAME} PRIVATE ${CXX_COMPILE_FLAGS})
target_compile_options(${PROJECT_NAME}_test PRIVATE ${CXX_COMPILE_FLAGS})

target_link_libraries(${PROJECT_NAME}_test 
        -L${CMAKE_CURRENT_SOURCE_DIR}/build 
        libcontainers.a)