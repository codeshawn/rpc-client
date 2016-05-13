cmake_minimum_required(VERSION 2.8)
project(rpc-client CXX)
file(GLOB SOURCES src/*.cpp src/*.h)
add_executable(rpc-client ${SOURCES})
target_link_libraries(rpc-client)
install(TARGETS rpc-client RUNTIME DESTINATION /usr/bin)

