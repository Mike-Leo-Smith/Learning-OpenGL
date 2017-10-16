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
    static auto distance = 5.0f;
    
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
    Window window("Multiple Lights", 800, 600);
    Shader boxShader("box.vert", "box.frag");
    Shader lightShader("box.vert", "light.frag");
    Texture diffuseTexture("container.png");
    Texture specularTexture("container_specular.png");
    
    glClearColor(0.1, 0.1, 0.1, 1.0);
    
    ArrayBuffer boxVbo;
    boxVbo.setBufferData(vertices, sizeof(vertices), GL_STATIC_DRAW);
    
    VertexArray boxVao;
    boxVao.setAttribPointer(boxVbo, 0, 3, 8, 0);
    boxVao.setAttribPointer(boxVbo, 1, 3, 8, 3);
    boxVao.setAttribPointer(boxVbo, 2, 2, 8, 6);
    
    VertexArray lightVao;
    lightVao.setAttribPointer(boxVbo, 0, 3, 8, 0);
    
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
    
    glm::vec3 pointLightPositions[] = {
        glm::vec3(0.7f, 0.2f, 2.0f),
        glm::vec3(2.3f, -3.3f, -4.0f),
        glm::vec3(-4.0f, 2.0f, -12.0f),
        glm::vec3(0.0f, 0.0f, -3.0f)
    };
    
    auto boxModel = glm::mat4();
    auto projection = glm::perspective(glm::radians(45.0f),
                                       static_cast<float>(window.width()) / window.height(), 0.1f, 100.0f);
    
    while (!window.shouldClose()) {
        
        auto cameraPos = updateCamera(window);
        auto view = glm::lookAt(cameraPos, glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
        boxVao.bind();
        boxShader.use();
        boxShader.setUniform("view", view);
        boxShader.setUniform("projection", projection);
        boxShader.setUniform("cameraPos", cameraPos);
        boxShader.setUniform("material.shininess", 32.0f);
        boxShader.setUniform("material.diffuse", 0);
        boxShader.setUniform("material.specular", 1);
        diffuseTexture.bind(0);
        specularTexture.bind(1);
    
        boxShader.setUniform("directionalLight.direction", glm::vec3(-0.2f, -1.0f, -0.3f));
        boxShader.setUniform("directionalLight.ambient", glm::vec3(0.05f));
        boxShader.setUniform("directionalLight.diffuse", glm::vec3(0.4f));
        boxShader.setUniform("directionalLight.specular", glm::vec3(0.5f));
        
        for (int i = 0; i < 4; i++) {
            boxShader.setUniform("pointLights["+ std::to_string(i) +"].position", pointLightPositions[i]);
            boxShader.setUniform("pointLights["+ std::to_string(i) +"].ambient", glm::vec3(0.05f));
            boxShader.setUniform("pointLights["+ std::to_string(i) +"].diffuse", glm::vec3(0.8f));
            boxShader.setUniform("pointLights["+ std::to_string(i) +"].specular", glm::vec3(1.0f));
            boxShader.setUniform("pointLights["+ std::to_string(i) +"].constant", 1.0f);
            boxShader.setUniform("pointLights["+ std::to_string(i) +"].linear", 0.09f);
            boxShader.setUniform("pointLights["+ std::to_string(i) +"].quadratic", 0.032f);
        }
        
        for (int i = 0; i < 10; i++) {
            glm::mat4 model;
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            boxShader.setUniform("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
    
        lightVao.bind();
        lightShader.use();
        lightShader.setUniform("view", view);
        lightShader.setUniform("projection", projection);
        lightShader.setUniform("lightColor", glm::vec3(1.0f));
        for (auto pointLightPosition : pointLightPositions) {
            auto scale = glm::scale(glm::mat4(), glm::vec3(0.15f));
            auto translation = glm::translate(glm::mat4(), pointLightPosition);
            lightShader.setUniform("model", translation * scale);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        
        window.swapBuffers();
        glfwPollEvents();
    }
    
    return 0;
}