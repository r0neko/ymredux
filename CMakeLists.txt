cmake_minimum_required(VERSION 3.23.0)
project(YMRedux)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(spdlog CONFIG REQUIRED)

# server app
add_executable(
        ${PROJECT_NAME}
        src/main.cpp
)

target_link_libraries(
        ${PROJECT_NAME}
        PRIVATE
        ws2_32
        spdlog::spdlog
)

# add src dir
target_include_directories(${PROJECT_NAME} PUBLIC src)