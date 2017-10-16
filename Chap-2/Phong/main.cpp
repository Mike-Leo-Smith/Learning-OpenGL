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
    auto deltaDistance = timeElapsed * 1.5f;
    lastTime = currTime;
    
    auto win = window.handler();
    
    if (glfwGetKey(win, GLFW_KEY_UP) || glfwGetKey(win, GLFW_KEY_W)) {
        theta += deltaAngle;
        if (theta > M_PI_2 - 0.05) {
            theta = static_cast<float>(M_PI_2 - 0.05);
        }
    } else if (glfwGetKey(win, GLFW_KEY_DOWN) || glfwGetKey(win, GLFW_KEY_S)) {
        theta -= deltaAngle;
        if (theta < -M_PI_2 + 0.05) {
            theta = static_cast<float>(-M_PI_2 + 0.05);
        }
    } else if (glfwGetKey(win, GLFW_KEY_LEFT) || glfwGetKey(win, GLFW_KEY_A)) {
        alpha -= deltaAngle;
    } else if (glfwGetKey(win, GLFW_KEY_RIGHT) || glfwGetKey(win, GLFW_KEY_D)) {
        alpha += deltaAngle;
    } else if (glfwGetKey(win, GLFW_KEY_MINUS)) {
        distance += deltaDistance;
        if (distance > 10.0f) {
            distance = 10.0f;
        }
    } else if (glfwGetKey(win, GLFW_KEY_EQUAL)) {
        distance -= deltaDistance;
        if (distance < 0.5f) {
            distance = 0.5f;
        }
    }
    
    return glm::vec3(sinf(alpha) * cosf(theta), sinf(theta), cosf(alpha) * cosf(theta)) * distance;
}

int main()
{
    Window window("Phong Lighting", 800, 600);
    Shader boxShader("box.vert", "box.frag");
    Shader lightShader("box.vert", "light.frag");
    
    glClearColor(0.1, 0.1, 0.1, 1.0);
    
    ArrayBuffer boxVbo;
    boxVbo.setBufferData(vertices, sizeof(vertices), GL_STATIC_DRAW);
    
    VertexArray boxVao;
    boxVao.setAttribPointer(boxVbo, 0, 3, 6, 0);
    boxVao.setAttribPointer(boxVbo, 1, 3, 6, 3);
    
    VertexArray lightVao;
    lightVao.setAttribPointer(boxVbo, 0, 3, 6, 0);
    
    auto boxModel = glm::mat4();
    auto lightPos = glm::vec3(1.5f, 1.0f, 2.0f);
    auto lightModel = glm::scale(glm::translate(glm::mat4(), lightPos), glm::vec3(0.2f));
    auto projection = glm::perspective(glm::radians(45.0f),
                                       static_cast<float>(window.width()) / window.height(), 0.1f, 100.0f);
    
    while (!window.shouldClose()) {
        
        auto cameraPos = updateCamera(window);
        auto view = glm::lookAt(cameraPos, glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
    
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        boxVao.bind();
        boxShader.use();
        boxShader.setUniform("model", boxModel);
        boxShader.setUniform("view", view);
        boxShader.setUniform("projection", projection);
        boxShader.setUniform("lightPos", lightPos);
        boxShader.setUniform("cameraPos", cameraPos);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        
        lightVao.bind();
        lightShader.use();
        lightShader.setUniform("model", lightModel);
        lightShader.setUniform("view", view);
        lightShader.setUniform("projection", projection);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        
        window.swapBuffers();
        glfwPollEvents();
    }
    
    return 0;
}