project("${PROJECT_NAME}-test" CXX)
set(TARGET_NAME "${PROJECT_NAME}")

conan_init()

enable_testing()

find_package(GMock REQUIRED)
list(APPEND LIBS GMock::GMock GMock::Main)

find_file(CATCH2_HEADER catch.hpp)

if (CATCH2_HEADER)
    get_filename_component(CATCH2_INCLUDE_DIR ${CATCH2_HEADER} DIRECTORY)

    add_library(Catch2 INTERFACE)
    target_include_directories(Catch2 INTERFACE ${CATCH2_INCLUDE_DIR})

    list(APPEND LIBS Catch2)

    get_filename_component(CATCH2_BASE_DIR ${CATCH2_INCLUDE_DIR} DIRECTORY)
    include(${CATCH2_BASE_DIR}/res/Catch.cmake)
endif ()

include(CodeCoverage)


add_source_directory(cpp SRCS HDRS)


add_executable(${TARGET_NAME} ${HDR} ${SRCS})
target_link_libraries(${TARGET_NAME} ratl ${LIBS})

catch_discover_tests(${TARGET_NAME})