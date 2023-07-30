cmake_minimum_required(VERSION 3.27)
project(opengl1)

# include glad
add_library(glad STATIC glad/src/gl.c)
include_directories(glad/include)

#include glfw
find_package(glfw3 REQUIRED)
include_directories(${GLFW_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 23)
add_executable(opengl1 main.cpp)

# link the library
target_link_libraries(opengl1 PRIVATE glfw glad ${CMAKE_DL_LIBS})