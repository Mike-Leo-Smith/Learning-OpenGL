cmake_minimum_required(VERSION 3.8)
project(Learning_OpenGL)

set(CMAKE_CXX_STANDARD 17)

include_directories(${CMAKE_SOURCE_DIR})

set(COMMON_FILES
    ThirdParty/GLAD/glad.c
    ThirdParty/GLAD/glad.h
    ThirdParty/GLAD/khrplatform.h
    ThirdParty/STB/stb_image.h
    ThirdParty/STB/stb_image.cpp
    Framework/Window/Window.cpp
    Framework/Window/Window.h
    Framework/Graphics/Shader.cpp
    Framework/Graphics/Shader.h
    Framework/Graphics/Texture.cpp
    Framework/Graphics/Texture.h
    Framework/Mathematics/Mathematics.h
    Framework/Mathematics/Vector.h)

add_executable(Triangles ${COMMON_FILES} Chap-1/Triangles/main.cpp)
target_link_libraries(Triangles glfw)

add_executable(Textures ${COMMON_FILES} Chap-1/Textures/main.cpp)
target_link_libraries(Textures glfw)

add_executable(Transforms ${COMMON_FILES} Chap-1/Transforms/main.cpp)
target_link_libraries(Transforms glfw)
