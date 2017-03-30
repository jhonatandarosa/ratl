project("${PROJECT_NAME}-test" CXX)
set(TARGET_NAME "${PROJECT_NAME}")

conan_init_config()
conan_add_package(catch 1.5.0 TyRoXx stable)
conan_add_package(gmock 1.8.0 meshell stable)

conan_install(BUILD_MISSING)

include(${PROJECT_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

find_package(GMock REQUIRED)
list(APPEND LIBS GMock::GMock GMock::Main)
include(CodeCoverage)


add_source_directory(cpp SRCS HDRS)


add_executable(${TARGET_NAME} ${HDR} ${SRCS})
target_link_libraries(${TARGET_NAME} ratl ${LIBS})