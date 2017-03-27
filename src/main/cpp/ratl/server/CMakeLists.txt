
file(GLOB HDRS *.h)
set(HDRS ${HDRS})

set(
    SRCS
    RestServer.cpp
)


set(SRCS ${SRCS} PARENT_SCOPE)
set(HDRS ${HDRS} PARENT_SCOPE)