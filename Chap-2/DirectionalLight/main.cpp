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
    Window window("Lighting Maps", 800, 600);
    Shader boxShader("box.vert", "box.frag");
    Texture diffuseTexture("container.png");
    Texture specularTexture("container_specular_color.png");
    
    glClearColor(0.1, 0.1, 0.1, 1.0);
    
    ArrayBuffer boxVbo;
    boxVbo.setBufferData(vertices, sizeof(vertices), GL_STATIC_DRAW);
    
    VertexArray boxVao;
    boxVao.setAttribPointer(boxVbo, 0, 3, 8, 0);
    boxVao.setAttribPointer(boxVbo, 1, 3, 8, 3);
    boxVao.setAttribPointer(boxVbo, 2, 2, 8, 6);
    
    glm::vec3 cubePositions[] = {
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(2.0f, 5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f, 3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),
        glm::vec3(1.5f, 2.0f, -2.5f),
        glm::vec3(1.5f, 0.2f, -1.5f),
        glm::vec3(-1.3f, 1.0f, -1.5f)
    };
    
    auto lightPos = glm::vec3(0.2f, 1.0f, 0.3f);
    auto projection = glm::perspective(
        glm::radians(45.0f), static_cast<float>(window.width()) / window.height(), 0.1f, 100.0f);
    
    while (!window.shouldClose()) {
    
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
        auto cameraPos = updateCamera(window);
        auto view = glm::lookAt(cameraPos, glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
        
        auto lightSpecular = glm::vec3(1.0f);
        auto lightDiffuse = lightSpecular * 0.5f;
        auto lightAmbient = lightSpecular * 0.2f;
        
        boxVao.bind();
        boxShader.use();
        boxShader.setUniform("view", view);
        boxShader.setUniform("projection", projection);
        boxShader.setUniform("cameraPos", cameraPos);
        boxShader.setUniform("material.shininess", 32.0f);
        boxShader.setUniform("light.direction", -lightPos);
        boxShader.setUniform("light.ambient", lightAmbient);
        boxShader.setUniform("light.diffuse", lightDiffuse);
        boxShader.setUniform("light.specular", lightSpecular);
        boxShader.setUniform("material.diffuse", 0);
        boxShader.setUniform("material.specular", 1);
        diffuseTexture.bind(0);
        specularTexture.bind(1);
    
        for (unsigned int i = 0; i < 10; i++) {
            glm::mat4 model;
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            boxShader.setUniform("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        
        window.swapBuffers();
        glfwPollEvents();
    }
    
    return 0;
}