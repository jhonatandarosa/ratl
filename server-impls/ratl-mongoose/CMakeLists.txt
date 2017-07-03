project(ratl-mongoose CXX)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMakeModules)
include(SourcesDirectories)
include_directories(/home/jhonatan.rosa/.conan/data/nlJson/2.0.1/arnemertz/testing/package/5ab84d6acfe1f23c4fae0ab88f26e3a396351ac9/include/)

add_subdirectory(src)
