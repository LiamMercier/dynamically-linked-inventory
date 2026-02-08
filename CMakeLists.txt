cmake_minimum_required(VERSION 3.25)
project(inventory LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(inventory
    main.cpp
)

target_compile_options(inventory PRIVATE
    -Wall -Wextra
)
