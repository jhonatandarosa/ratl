set(TARGET_NAME ${PROJECT_NAME})

add_source_directory(cpp SRCS HDRS)
# FIXME ???
set_source_files_properties(
        cpp/mongoose/mongoose.h
        cpp/mongoose/mongoose.c
        PROPERTIES LANGUAGE CXX
)

add_library(${TARGET_NAME} ${HDRS} ${SRCS})
target_include_directories(${TARGET_NAME} PUBLIC cpp)
target_link_libraries(${TARGET_NAME} ratl)