cmake_minimum_required(VERSION 3.2.2)

add_subdirectory(server-impls)
add_subdirectory(examples)

project(ratl)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMakeModules)
include(SourcesDirectories)
include(ConanUtils)

conan_add_package(catch 1.5.0 TyRoXx stable)
conan_add_package(nlJson 2.0.1 arnemertz testing)

if (CMAKE_COMPILER_IS_GNUCC AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS 4.9)
conan_add_package(
    Boost 1.60.0 lasote stable
    fPIC=True
    without_regex=False

    without_atomic=True
    without_chrono=True
    without_container=True
    without_context=True
    without_coroutine=True
    without_coroutine2=True
    without_date_time=True
    without_exception=True
    without_filesystem=True
    without_graph=True
    without_graph_parallel=True
    without_iostreams=True
    without_locale=True
    without_log=True
    without_math=True
    without_mpi=True
    without_program_options=True
    without_random=True
    without_serialization=True
    without_signals=True
    without_system=True
    without_test=True
    without_thread=True
    without_timer=True
    without_type_erasure=True
    without_wave=True
)
set(_USE_BOOST_REGEX True)
add_definitions(-D_USE_BOOST_REGEX=1)
endif()
conan_install(BUILD_MISSING)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-g -O0 --coverage")
set(CMAKE_C_FLAGS "-g -O0 --coverage")

add_subdirectory(src)