file(GLOB HDRS *.h)
set(HDRS ${HDRS})

set(
        SRCS
        MockNetIO.cpp
)


set(SRCS ${SRCS} PARENT_SCOPE)
set(HDRS ${HDRS} PARENT_SCOPE)