cmake_minimum_required(VERSION 3.1)
project(template_common VERSION 1.0)

option(TEMPLATE_COMMON_TEST "build test" OFF)
if(TEMPLATE_COMMON_TEST)
    message("template_common tests are going to be build as well")
else()
    message("ignore building tests for template_common")
endif()

set(CMAKE_BUILD_TYPE "Release")
set(DEPS_DIR ${CMAKE_BINARY_DIR}/tmp CACHE STRING "Dependency directory")
get_filename_component(DEPS_DIR ${DEPS_DIR} REALPATH BASE_DIR ${CMAKE_BINARY_DIR})

add_definitions(-std=c++2a -Wno-deprecated-copy)
include_directories(template_common PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

if(TEMPLATE_COMMON_TEST)
    add_subdirectory(test)
endif()
