project(nlohmann_json CXX)

set(TARGET_NAME ${PROJECT_NAME})
add_library(${TARGET_NAME} INTERFACE)
target_include_directories(${TARGET_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})