add_source_directory(ratl SRCS HDRS)
add_source_directory(mock SRCS HDRS)
set(
        SRCS
        ${SRCS}
        main.cpp
)


set(SRCS ${SRCS} PARENT_SCOPE)
set(HDRS ${HDRS} PARENT_SCOPE)