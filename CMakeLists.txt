cmake_minimum_required(VERSION 3.10)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_STANDARD 11)

project(my-linux-commands)

add_subdirectory(cat)
add_subdirectory(echo)
add_subdirectory(head)