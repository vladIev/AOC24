cmake_minimum_required(VERSION 3.27)

project(template_project)

include(CTest)
enable_testing()

include("${CMAKE_SOURCE_DIR}/cmake/utils.cmake")

find_package(GTest REQUIRED)
find_package(benchmark REQUIRED)

include_directories(${benchmark_INCLUDE_DIRS})
add_subdirectory("${CMAKE_SOURCE_DIR}/src")


add_main_targets()
add_test_targets()
add_benchmark_targets()

