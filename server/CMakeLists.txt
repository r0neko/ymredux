project(server)

add_executable(
  ${PROJECT_NAME}
  src/main.cpp
)

target_compile_features(
  ${PROJECT_NAME}
  PRIVATE
  cxx_std_23
)
