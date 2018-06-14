cmake_minimum_required(VERSION 3.2.2)

add_subdirectory(server-impls)
add_subdirectory(examples)
add_subdirectory(thirdparty)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMakeModules)
include(SourcesDirectories)
include(ConanUtils)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-g -O0 --coverage")
set(CMAKE_C_FLAGS "-g -O0 --coverage")

add_subdirectory(src)