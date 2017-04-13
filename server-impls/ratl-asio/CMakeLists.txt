project(ratl-asio CXX)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMakeModules)
include(SourcesDirectories)

include(ConanUtils)

conan_init_config()
conan_add_package(
        Boost 1.60.0 lasote stable
        without_system=False
        fPIC=True
        without_regex=True
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
        without_test=True
        without_thread=True
        without_timer=True
        without_type_erasure=True
        without_wave=True
)
conan_install(BUILD_MISSING)

include(${PROJECT_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_subdirectory(src)