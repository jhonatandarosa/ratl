set(TARGET_NAME ${PROJECT_NAME})


#hunter_add_package(nlohmann-json)
#find_package(nlohmann-json REQUIRED)
#list(APPEND LIBS nlohmann-json::nlohmann-json)
#
#hunter_add_package(Boost COMPONENTS regex)
#find_package(Boost CONFIG REQUIRED regex)
if(_USE_BOOST_REGEX)
    list(APPEND LIBS boost_regex)
endif()

include_directories(cpp)
add_source_directory(cpp SRCS HDRS)

add_library(${TARGET_NAME} ${HDRS} ${SRCS})
target_link_libraries(${TARGET_NAME} ${LIBS})