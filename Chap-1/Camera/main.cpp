#include <iostream>
#include <ThirdParty/GLAD/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Framework/Window/Window.h"
#include "Framework/Graphics/Graphics.h"
#include "vertices.h"

glm::vec3 updateCamera(Window &window)
{
    static auto alpha = 0.0f;
    static auto theta = 0.0f;
    static auto lastTime = 0.0f;
    static auto distance = 4.0f;
    
    auto currTime = static_cast<float>(glfwGetTime());
    auto timeElapsed = currTime - lastTime;
    auto deltaAngle = timeElapsed * 2.0f;
    auto deltaDistance = timeElapsed * 2.0f;
    lastTime = currTime;
    
    auto win = window.handler();
    
    if (glfwGetKey(win, GLFW_KEY_UP) || glfwGetKey(win, GLFW_KEY_W)) {
        theta += deltaAngle;
        if (theta > M_PI_2 - 0.05) {
            theta = static_cast<float>(M_PI_2 - 0.05);
        }
    }
    if (glfwGetKey(win, GLFW_KEY_DOWN) || glfwGetKey(win, GLFW_KEY_S)) {
        theta -= deltaAngle;
        if (theta < -M_PI_2 + 0.05) {
            theta = static_cast<float>(-M_PI_2 + 0.05);
        }
    }
    if (glfwGetKey(win, GLFW_KEY_LEFT) || glfwGetKey(win, GLFW_KEY_A)) {
        alpha -= deltaAngle;
    }
    if (glfwGetKey(win, GLFW_KEY_RIGHT) || glfwGetKey(win, GLFW_KEY_D)) {
        alpha += deltaAngle;
    }
    if (glfwGetKey(win, GLFW_KEY_MINUS)) {
        distance += deltaDistance;
        if (distance > 10.0f) {
            distance = 10.0f;
        }
    }
    if (glfwGetKey(win, GLFW_KEY_EQUAL)) {
        distance -= deltaDistance;
        if (distance < 0.5f) {
            distance = 0.5f;
        }
    }
    
    return glm::vec3(sinf(alpha) * cosf(theta), sinf(theta), cosf(alpha) * cosf(theta)) * distance;
}

int main()
{
    Window window("Camera", 800, 600);
    Shader shader("shader.vert", "shader.frag");
    Texture boxTexture("container.jpg");
    Texture faceTexture("awesomeface.png");
    
    glClearColor(0.2, 0.3, 0.4, 1.0);
    
    ArrayBuffer vbo;
    vbo.setBufferData(vertices, sizeof(vertices), GL_STATIC_DRAW);
    
    VertexArray vao;
    vao.setAttribPointer(vbo, 0, 3, 5, 0);
    vao.setAttribPointer(vbo, 1, 2, 5, 3);
    
    shader.use();
    
    boxTexture.bind(0);
    shader.setUniform("boxSampler", 0);
    faceTexture.bind(1);
    shader.setUniform("faceSampler", 1);
    
    vao.bind();
    
    auto model = glm::mat4();
    auto projection = glm::perspective(glm::radians(45.0f),
                                       static_cast<float>(window.width()) / window.height(), 0.1f, 100.0f);
    
    while (!window.shouldClose()) {
        auto view = glm::lookAt(updateCamera(window), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
        shader.setUniform("transform", projection * view * model);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        window.swapBuffers();
        glfwPollEvents();
    }
    
    return 0;
}