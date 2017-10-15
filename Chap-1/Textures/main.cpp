#include "ThirdParty/GLAD/glad.h"
#include "ThirdParty/STB/stb_image.h"
#include "Framework/Window/Window.h"
#include "Framework/Graphics/Shader.h"
#include "Framework/Graphics/Texture.h"

int main() {
    Window window("Textures", 800, 600);
    Shader shader("box.vert", "box.frag");
    Texture texture1("container.jpg");
    Texture texture2("awesomeface.png");

    float vertices[] = {
        //     位置        |       颜色      |   纹理坐标
        0.5f,  0.5f,  0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // 右上
        0.5f,  -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // 右下
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // 左下
        -0.5f, 0.5f,  0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f  // 左上
    };

    unsigned int vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    unsigned int vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), static_cast<float *>(nullptr) + 3);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), static_cast<float *>(nullptr) + 6);
    glEnableVertexAttribArray(2);

    glClearColor(0.2, 0.3, 0.4, 1.0);

    glBindVertexArray(vao);
    shader.use();

    shader.setUniform("texSampler", 0);
    texture1.bind(0);

    shader.setUniform("anotherTexSampler", 1);
    texture2.bind(1);
    
    while (!window.shouldClose()) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
        window.swapBuffers();
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glfwTerminate();

    return 2333;
}
