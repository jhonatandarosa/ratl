project(basicserver CXX)

set(CMAKE_CXX_STANDARD 11)
set(SRCS
    main.cpp
)
include_directories(/home/jhonatan.rosa/.conan/data/nlJson/2.0.1/arnemertz/testing/package/5ab84d6acfe1f23c4fae0ab88f26e3a396351ac9/include/)
add_executable(basicserver ${SRCS})
target_link_libraries(basicserver ratl ratl-mongoose)