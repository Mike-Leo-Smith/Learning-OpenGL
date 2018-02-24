#include <random>
#include <iostream>
#include "Framework/Graphics/Graphics.h"
#include "Framework/Window/Window.h"

int main()
{
    Window window{ "Hello", 512, 256 };
    Shader shader("shader.vert", "shader.frag");
    
    constexpr float vertices[]{
        -1.0f, 1.0f, 0.0f, 0.0f,
        -1.0f, -1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 1.0f, 0.0f,
        -1.0f, -1.0f, 0.0f, 1.0f,
        1.0f, -1.0f, 1.0f, 1.0f
    };
    
    VertexBuffer vbo;
    vbo.setData(vertices, sizeof(vertices), GL_STATIC_DRAW);
    VertexArray vao;
    vao.setAttribPointer(vbo, 0, 2, 4, 0);
    vao.setAttribPointer(vbo, 1, 2, 4, 2);
    
    glClearColor(0.2, 0.3, 0.4, 1.0);
    
    constexpr auto width = 128;
    constexpr auto height = 64;
    constexpr auto channels = 3;
    std::vector<char> pixels;
    pixels.resize(width * height * channels);
    
    std::default_random_engine random_engine(std::random_device{}());
    std::uniform_int_distribution<int> random_pixel(0, width * height * channels - 1);
    std::uniform_int_distribution<unsigned char> random_color(0, 255);
    
    Texture2D texture{ pixels, width, height, channels };
    texture.bind(0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    texture.unbind();
    
    shader.use();
    shader.setUniform("sampler", 0);
    vao.bind();
    
    while (!window.shouldClose()) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        for (auto i = 0; i < 10; i++) {
            pixels[random_pixel(random_engine)] = random_color(random_engine);
        }
        texture.subPixels(pixels);
        texture.bind(0);
        
        glDrawArrays(GL_TRIANGLES, 0, 6);
        window.swapBuffers();
        glfwPollEvents();
    }
}