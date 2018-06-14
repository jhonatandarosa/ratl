add_source_directory(rest SRCS HDRS)
add_source_directory(router SRCS HDRS)
add_source_directory(server SRCS HDRS)

set(
        SRCS
        ${SRCS}
)


set(SRCS ${SRCS} PARENT_SCOPE)
set(HDRS ${HDRS} PARENT_SCOPE)