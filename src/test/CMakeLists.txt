set(TARGET_NAME "${PROJECT_NAME}-test")

include(CodeCoverage)


include_directories(../main/cpp)
#include_directories(../../../thirdparty/FakeIt-2.0.2/include)
#include_directories(../../../thirdparty/FakeIt-2.0.2/config/catch)

#hunter_add_package(Catch)
#find_package(Catch CONFIG REQUIRED)
#list(APPEND LIBS Catch::Catch)

#add_definitions(-DGTEST_HAS_PTHREAD=0)
#hunter_add_package(GTest)
#find_package(GMock CONFIG REQUIRED)
#list(APPEND LIBS GMock::main)

add_source_directory(cpp SRCS HDRS)
#add_subdirectory(resources)
#list(APPEND LIBS boost_regex)

add_executable(${TARGET_NAME} ${HDR} ${SRCS})
target_link_libraries(${TARGET_NAME} ${LIBS} ${PROJECT_NAME})

set(LCOV_REMOVE_EXTRA "'.conan/*'" "'*test/*'")
setup_target_for_coverage("${PROJECT_NAME}-coverage" ${TARGET_NAME} "coverage")