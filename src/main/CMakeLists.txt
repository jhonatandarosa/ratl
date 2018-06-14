set(TARGET_NAME ${PROJECT_NAME})

conan_init()

list(APPEND LIBS nlohmann_json)

add_source_directory(cpp SRCS HDRS)

add_library(${TARGET_NAME} SHARED ${HDRS} ${SRCS})
target_include_directories(${TARGET_NAME} PUBLIC cpp)
target_link_libraries(${TARGET_NAME} ${LIBS})