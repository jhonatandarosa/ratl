add_source_directory(rest SRCS HDRS)
add_source_directory(router SRCS HDRS)
add_source_directory(server SRCS HDRS)

file(GLOB headers *.h)
set(HDRS ${HDRS} ${headers})

set(
        SRCS
        ${SRCS}
)


set(SRCS ${SRCS} PARENT_SCOPE)
set(HDRS ${HDRS} PARENT_SCOPE)