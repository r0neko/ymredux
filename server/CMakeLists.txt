project(server)

find_package(spdlog CONFIG REQUIRED)

add_executable(
  ${PROJECT_NAME}
  src/main.cpp
)

target_compile_features(
  ${PROJECT_NAME}
  PRIVATE
  cxx_std_23
)

target_link_libraries(
  ${PROJECT_NAME}
  PRIVATE
  ws2_32
  spdlog::spdlog
)
