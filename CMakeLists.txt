cmake_minimum_required(VERSION 3.27)
project(YMRedux)

set(CMAKE_CXX_STANDARD 23)

add_executable(YMRedux
        src/main.cpp

        src/core/tcp_connection.cpp
        src/core/tcp_server.cpp

        src/ymsg/ymsg_connection.cpp
        src/ymsg/ymsg_frame_field.cpp
)

target_include_directories(YMRedux PUBLIC src)
