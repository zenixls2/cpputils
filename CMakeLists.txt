cmake_minimum_required(VERSION 3.1)
project(cpputils VERSION 1.0)

option(TEMPLATE_COMMON_TEST "build test" OFF)
if(CPPUTILS_TEST)
    message("cpputils tests are going to be build as well")
else()
    message("ignore building tests for cpputils")
endif()

set(CMAKE_BUILD_TYPE "Release")
set(DEPS_DIR ${CMAKE_BINARY_DIR}/tmp CACHE STRING "Dependency directory")
get_filename_component(DEPS_DIR ${DEPS_DIR} REALPATH BASE_DIR ${CMAKE_BINARY_DIR})

find_library(quadmath NAMES quadmath.a)
add_definitions(-std=c++2a -Wno-deprecated-copy -fext-numeric-literals)

file(GLOB_RECURSE sources ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
find_library(quadmath quadmath.a)

add_library(cpputils STATIC ${sources})
target_include_directories(cpputils PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(cpputils quadmath)

if(CPPUTILS_TEST)
    add_subdirectory(test)
endif()
