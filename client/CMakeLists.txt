cmake_minimum_required(VERSION 3.5)

project(client)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -fsanitize=address,undefined -g")

file(GLOB_RECURSE SOURCES . src/*.c)

add_executable(client ${SOURCES})
