cmake_minimum_required(VERSION 3.8)
project(Learning_OpenGL)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -framework OpenGL -lglfw -lglew")

include_directories(Common)
set(COMMON_FILES
    Common/Window.cpp
    Common/Window.h
    Common/Shader.cpp
    Common/Shader.h
    Common/Mathematics.h
    Common/Vector.h)

add_executable(Triangles ${COMMON_FILES} Chap-1/Triangles/main.cpp)