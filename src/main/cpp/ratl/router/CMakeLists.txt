
file(GLOB HDRS *.h)
set(HDRS ${HDRS})

set(
        SRCS
        RTrie.cpp
        RTrieNode.cpp
        RTrieMatch.cpp
        RTrieException.cpp
)


set(SRCS ${SRCS} PARENT_SCOPE)
set(HDRS ${HDRS} PARENT_SCOPE)