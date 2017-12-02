cmake_minimum_required(VERSION 3.8)
project(Learning_OpenGL)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3 -march=native -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -march=native -Wall")

link_libraries(glfw assimp freetype)
include_directories(${CMAKE_SOURCE_DIR} /usr/local/include/freetype2)

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
    Framework/Graphics/Texture2D.cpp
    Framework/Graphics/Texture2D.h
    Framework/Mathematics/Mathematics.h
    Framework/Mathematics/Vector.h
    Framework/Mathematics/Matrix.h
    Framework/Graphics/VertexArray.cpp
    Framework/Graphics/VertexArray.h
    Framework/Graphics/Graphics.h
    Framework/Model/Mesh.cpp
    Framework/Model/Mesh.h
    Framework/Graphics/Vertex.h
    Framework/Model/Model.cpp
    Framework/Model/Model.h
    Framework/Graphics/Texture.cpp
    Framework/Graphics/Texture.h
    Framework/Graphics/CubeMap.cpp
    Framework/Graphics/CubeMap.h
    Framework/Text/Font.cpp
    Framework/Text/Font.h
    Framework/Text/Glyph.cpp
    Framework/Text/Glyph.h
    Framework/Graphics/Buffer.h
    Framework/Text/Text.cpp
    Framework/Text/Text.h
    Framework/Graphics/GLDataType.h
    Framework/Graphics/VertexBuffer.h
    Framework/Graphics/ElementBuffer.h)

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
add_executable(Models ${COMMON_FILES} Chap-3/Models/main.cpp)
add_executable(StencilTesting ${COMMON_FILES} Chap-4/StencilTesting/main.cpp)
add_executable(CubeMaps ${COMMON_FILES} Chap-4/CubeMaps/main.cpp)
add_executable(EnvironmentMapping ${COMMON_FILES} Chap-4/EnvironmentMapping/main.cpp)
add_executable(TextRendering ${COMMON_FILES} Chap-8/TextRendering/main.cpp)
