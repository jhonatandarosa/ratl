add_source_directory(ratl SRCS HDRS)

file(GLOB headers *.h)
set(HDRS ${HDRS} ${headers})

set(
        SRCS
        ${SRCS}
)


set(SRCS ${SRCS} PARENT_SCOPE)
set(HDRS ${HDRS} PARENT_SCOPE)