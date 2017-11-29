#include <cmath>

#include "ThirdParty/GLAD/glad.h"
#include "Framework/Graphics/Graphics.h"
#include "Framework/Window/Window.h"

int main()
{
    Window window("Hello, Triangle!", 800, 600);
    Shader shader("shader.vert", "shader.frag");
    
    glClearColor(0.2, 0.3, 0.4, 1.0);
    
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.5f, 0.0f,
        0.0f, 0.0f, 1.0f
    };
    
    VertexBuffer vbo;
    vbo.setData(vertices, sizeof(vertices), GL_STATIC_DRAW);
    
    VertexArray vao;
    vao.setAttribPointer(vbo, 0, 3, 6, 0);
    vao.setAttribPointer(vbo, 1, 3, 6, 3);
    
    shader.use();
    vao.bind();
    
    while (!window.shouldClose()) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        shader.setUniform("alpha", sinf(static_cast<float>(glfwGetTime())) * 0.5f + 0.5f);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        window.swapBuffers();
        glfwPollEvents();
    }
    
    return 0;
}