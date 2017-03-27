set(TARGET_NAME ${PROJECT_NAME})


if(_USE_BOOST_REGEX)
    list(APPEND LIBS boost_regex)
endif()

include_directories(cpp)
add_source_directory(cpp SRCS HDRS)

add_library(${TARGET_NAME} SHARED ${HDRS} ${SRCS})
target_link_libraries(${TARGET_NAME} ${LIBS})