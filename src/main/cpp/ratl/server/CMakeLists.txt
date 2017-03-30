
file(GLOB HDRS *.h)
set(HDRS ${HDRS})

set(
        SRCS
        RestServer.cpp
        NetIO.cpp
)


set(SRCS ${SRCS} PARENT_SCOPE)
set(HDRS ${HDRS} PARENT_SCOPE)