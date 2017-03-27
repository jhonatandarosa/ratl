project(basicserver CXX)

set(CMAKE_CXX_STANDARD 11)
set(SRCS
    main.cpp
)

add_executable(basicserver ${SRCS})
target_link_libraries(basicserver ratl ratl-asio)