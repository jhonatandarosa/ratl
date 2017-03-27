project(ratl-asio CXX)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMakeModules)
include(SourcesDirectories)

add_subdirectory(src)