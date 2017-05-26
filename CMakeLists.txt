cmake_minimum_required(VERSION 2.4)

PROJECT(linmaze)
SET(CMAKE_VERBOSE_MAKEFILE ON)
ADD_DEFINITIONS(-Wall -O2)
ADD_EXECUTABLE(linmaze main.cpp Level3D.cpp OpenGL.cpp)
TARGET_LINK_LIBRARIES(linmaze GL GLU SDL2)
