
file(GLOB headers *.h)
set(HDRS ${HDRS} ${headers})

set(
        SRCS
        ${SRCS}
        RestAPI.cpp
        Router.cpp
        Resource.cpp
        Request.cpp
)


set(SRCS ${SRCS} PARENT_SCOPE)
set(HDRS ${HDRS} PARENT_SCOPE)