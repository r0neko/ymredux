cmake_minimum_required(VERSION 3.23.0)
project(YMRedux)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(spdlog CONFIG REQUIRED)

# server app
add_executable(
        ${PROJECT_NAME}
        src/main.cpp
        src/server/server.cpp
        src/server/handlers/helo.cpp
        src/server/handlers/login_stage2.cpp
        src/server/handlers/port_check.cpp
)

target_link_libraries(
        ${PROJECT_NAME}
        PRIVATE
        ws2_32
        spdlog::spdlog
)

# add src dir
target_include_directories(${PROJECT_NAME} PUBLIC src)