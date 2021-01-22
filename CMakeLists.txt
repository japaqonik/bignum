cmake_minimum_required(VERSION 3.10)

# set the project name
project(crypto)

add_library(ubigint_t STATIC src/ubigint_t.cpp)

add_executable(main main.cpp)

target_link_libraries(main ubigint_t)