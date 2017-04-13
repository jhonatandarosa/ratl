add_source_directory(detail HDRS SRCS)
file(GLOB hdrs *.h)
set(HDRS ${HDRS} ${hdrs})


set(
        SRCS
        ${SRCS}
        BoostASIONetIO.cpp
)
set(SRCS ${SRCS} PARENT_SCOPE)
set(HDRS ${HDRS} PARENT_SCOPE)