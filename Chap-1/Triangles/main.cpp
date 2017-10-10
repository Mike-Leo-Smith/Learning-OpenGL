#include <GL/glew.h>
#include <cmath>

#include "Shader.h"
#include "Window.h"

int main() {
    Window window("Hello, Triangle!", 800, 600);
    Shader shader("shader.vert", "shader.frag");
    
    glClearColor(0.3, 0.4, 0.5, 1.0);

    float vertices[] = {
        -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // Left.
        0.5f,  -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // Right.
        0.0f,  0.5f,  0.0f, 0.0f, 0.0f, 1.0f  // Up.
    };

    unsigned int vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    unsigned int vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), static_cast<float *>(nullptr) + 3);
    glEnableVertexAttribArray(1);

    shader.use();
    glBindVertexArray(vao);

    while (!window.shouldClose()) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        window.swapBuffers();
        glfwPollEvents();
        shader.setUniform("alpha", sinf(static_cast<float>(glfwGetTime())) * 0.5f + 0.5f);
    }

    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);

    glfwTerminate();

    return 0;
}