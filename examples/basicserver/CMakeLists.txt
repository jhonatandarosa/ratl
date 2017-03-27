project(basicserver CXX)


set(SRCS
    main.cpp
)

add_executable(basicserver ${SRCS})
target_link_libraries(basicserver ratl ratl-asio)