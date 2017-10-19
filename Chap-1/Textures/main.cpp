#include "ThirdParty/GLAD/glad.h"
#include "Framework/Window/Window.h"
#include "Framework/Graphics/Graphics.h"

int main()
{
    Window window("Textures", 800, 600);
    Shader shader("shader.vert", "shader.frag");
    Texture2D texture1("container.jpg");
    Texture2D texture2("awesomeface.png");
    
    float vertices[] = {
        //     位置        |       颜色      |   纹理坐标
        0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // 右上
        0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // 右下
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // 左下
        -0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f  // 左上
    };
    
    unsigned int indices[] {
        0, 1, 3,
        1, 2, 3
    };
    
    VertexBuffer vbo;
    vbo.setBufferData(vertices, sizeof(vertices), GL_STATIC_DRAW);
    
    ElementBuffer ebo;
    ebo.setBufferData(indices, sizeof(indices), GL_STATIC_DRAW);
    
    VertexArray vao;
    vao.setAttribPointer(vbo, 0, 3, 8, 0);
    vao.setAttribPointer(vbo, 1, 3, 8, 3);
    vao.setAttribPointer(vbo, 2, 2, 8, 6);
    
    glClearColor(0.2, 0.3, 0.4, 1.0);
    
    shader.use();
    shader.setUniform("texSampler", 0);
    texture1.bind(0);
    shader.setUniform("anotherTexSampler", 1);
    texture2.bind(1);
    
    vao.bind();
    
    while (!window.shouldClose()) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        ebo.bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        window.swapBuffers();
        glfwPollEvents();
    }
    
    return 0;
}
