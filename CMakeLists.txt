cmake_minimum_required(VERSION 3.6)

project(ratl)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMakeModules)
include(SourcesDirectories)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-g -O0 --coverage")
set(CMAKE_C_FLAGS "-g -O0 --coverage")

add_subdirectory(src)