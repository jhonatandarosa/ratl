file(GLOB hdrs *.h)
set(HDRS ${HDRS} ${hdrs})

set(
        SRCS
        ${SRCS}
        MongooseNetIO.cpp
)
set(SRCS ${SRCS} PARENT_SCOPE)
set(HDRS ${HDRS} PARENT_SCOPE)