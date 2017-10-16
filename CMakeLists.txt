cmake_minimum_required(VERSION 3.8)
project(Learning_OpenGL)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0 -march=native -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -march=native -Wall")

link_libraries(glfw)
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
    Framework/Mathematics/Vector.h
    Framework/Mathematics/Matrix.h
    Framework/Graphics/VertexArray.cpp
    Framework/Graphics/VertexArray.h
    Framework/Graphics/ArrayBuffer.cpp
    Framework/Graphics/ArrayBuffer.h
    Framework/Graphics/Graphics.h
    Framework/Graphics/Buffer.h
    Framework/Graphics/Buffer.cpp)

add_executable(Triangles ${COMMON_FILES} Chap-1/Triangles/main.cpp)
add_executable(Textures ${COMMON_FILES} Chap-1/Textures/main.cpp)
add_executable(Transformations ${COMMON_FILES} Chap-1/Transformations/main.cpp)
add_executable(Camera ${COMMON_FILES} Chap-1/Camera/main.cpp)
add_executable(Phong ${COMMON_FILES} Chap-2/Phong/main.cpp)
add_executable(Materials ${COMMON_FILES} Chap-2/Materials/main.cpp)
add_executable(LightingMaps ${COMMON_FILES} Chap-2/LightingMaps/main.cpp)
add_executable(DirectionalLight ${COMMON_FILES} Chap-2/DirectionalLight/main.cpp)
add_executable(PointLight ${COMMON_FILES} Chap-2/PointLight/main.cpp)
add_executable(SpotLight ${COMMON_FILES} Chap-2/SpotLight/main.cpp)
add_executable(MultipleLights ${COMMON_FILES} Chap-2/MultipleLights/main.cpp)