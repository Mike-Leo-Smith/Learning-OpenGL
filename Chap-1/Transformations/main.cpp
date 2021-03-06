#include <iostream>
#include <ThirdParty/GLAD/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Framework/Window/Window.h"
#include "Framework/Graphics/Graphics.h"
#include "vertices.h"

int main()
{
    Window window("Transformations", 800, 600);
    Shader shader("shader.vert", "shader.frag");
    Texture2D boxTexture("container.jpg");
    Texture2D faceTexture("awesomeface.png");
    
    glClearColor(0.2, 0.2, 0.2, 1.0);
    
    VertexBuffer vbo;
    vbo.setData(vertices, sizeof(vertices), GL_STATIC_DRAW);
    
    VertexArray vao;
    vao.setAttribPointer(vbo, 0, 3, 5, 0);
    vao.setAttribPointer(vbo, 1, 2, 5, 3);
    
    shader.use();
    boxTexture.bind(0);
    shader.setUniform("boxSampler", 0);
    faceTexture.bind(1);
    shader.setUniform("faceSampler", 1);
    
    vao.bind();
    
    while (!window.shouldClose()) {
        auto size = static_cast<float>(sin(glfwGetTime() * 3)) * 0.25 + 1.0f;
        auto translation = glm::translate(glm::mat4(), glm::vec3(static_cast<float>(0.75 * cos(glfwGetTime())),
                                                                 static_cast<float>(0.75 * sin(glfwGetTime())), 0));
        auto rotation = glm::rotate(glm::mat4(), static_cast<float>(glfwGetTime()), glm::vec3(0.0f, 0.0f, 1.0f));
        auto scale = glm::scale(glm::mat4(), glm::vec3(size, size, size));
        auto model = translation * rotation * scale;
        
        auto view = glm::translate(glm::mat4(), glm::vec3(0, 0, -4.0f))
            * glm::rotate(glm::mat4(), glm::radians(-45.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        
        auto proj = glm::perspective(glm::radians(45.0f),
                                     static_cast<float>(window.width()) / window.height(), 0.1f, 100.0f);
        
        shader.setUniform("transform", proj * view * model);
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices) / sizeof(float) / 5);
        window.swapBuffers();
        glfwPollEvents();
    }
    
    return 0;
}
