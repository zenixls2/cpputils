find_package(Threads REQUIRED)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include(ExternalProject)
set(gtest googletest_template_common)
ExternalProject_Add(${gtest}
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.8.0
    INSTALL_COMMAND "")
set(GTEST_INCLUDE_DIR ${CMAKE_CURRENT_BINARY_DIR}/${gtest}-prefix/src/${gtest}/googletest/include)
set(GTEST_LIB_DIR ${CMAKE_CURRENT_BINARY_DIR}/${gtest}-prefix/src/${gtest}-build/googlemock/)
find_library(quadmath NAMES quadmath.a)
set(TARGET
    ${GTEST_LIB_DIR}/gtest/libgtest_main.a
    ${GTEST_LIB_DIR}/gtest/libgtest.a
    ${CMAKE_THREAD_LIBS_INIT}
    quadmath)
include_directories(BEFORE ${GTEST_INCLUDE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../include
    ${CMAKE_CURRENT_SOURCE_DIR}/../test/include)

add_executable(test_type_identity test_type_identity.cpp)
target_link_libraries(test_type_identity ${TARGET})
add_dependencies(test_type_identity googletest_template_common)

add_executable(test_mathlib test_mathlib.cpp ${CMAKE_CURRENT_SOURCE_DIR}/../src/mathlib.cpp)
target_link_libraries(test_mathlib ${TARGET})
add_dependencies(test_mathlib googletest_template_common)

add_definitions(-O3)
#set(CMAKE_CXX_FLAGS "-Wno-error=deprecated-copy")
enable_testing()
add_test(NAME test_type_identity COMMAND test_type_identity)
add_test(NAME test_mathlib COMMAND test_mathlib)


