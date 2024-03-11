cmake_minimum_required(VERSION 3.25.0)

project(ymredux)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_compile_options(
  -Wall
  -Wextra
  -Wpedantic
  -Wno-microsoft
  -fno-exceptions
  -fno-rtti
)

add_subdirectory(server)
