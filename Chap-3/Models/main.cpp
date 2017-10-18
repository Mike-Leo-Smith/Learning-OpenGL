#include <iostream>
#include <ThirdParty/GLAD/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Framework/Window/Window.h"
#include "Framework/Graphics/Graphics.h"
#include "Framework/Model/Model.h"
#include "vertices.h"

void updateCamera(Window &window, glm::vec3 &cameraPos, glm::vec3 &lookAt)
{
    static auto alpha = 0.0f;
    static auto theta = 0.0f;
    static auto lastTime = 0.0f;
    static auto distance = 15.0f;
    static auto x = 0.0f;
    static auto y = 10.0f;
    
    auto currTime = static_cast<float>(glfwGetTime());
    auto timeElapsed = currTime - lastTime;
    auto deltaAngle = timeElapsed * 2.0f;
    auto deltaDistance = timeElapsed * 10.0f;
    lastTime = currTime;
    
    auto win = window.handler();
    
    if (glfwGetKey(win, GLFW_KEY_UP)) {
        theta += deltaAngle;
        if (theta > M_PI_2 - 0.05) {
            theta = static_cast<float>(M_PI_2 - 0.05);
        }
    }
    if (glfwGetKey(win, GLFW_KEY_DOWN)) {
        theta -= deltaAngle;
        if (theta < -M_PI_2 + 0.05) {
            theta = static_cast<float>(-M_PI_2 + 0.05);
        }
    }
    if (glfwGetKey(win, GLFW_KEY_LEFT)) {
        alpha -= deltaAngle;
    }
    if (glfwGetKey(win, GLFW_KEY_RIGHT)) {
        alpha += deltaAngle;
    }
    
    if (glfwGetKey(win, GLFW_KEY_MINUS)) {
        distance += deltaDistance;
    }
    if (glfwGetKey(win, GLFW_KEY_EQUAL)) {
        distance -= deltaDistance;
        if (distance < 0.2f) {
            distance = 0.2f;
        }
    }
    
    if (glfwGetKey(win, GLFW_KEY_W)) {
        y += deltaDistance;
    }
    if (glfwGetKey(win, GLFW_KEY_S)) {
        y -= deltaDistance;
    }
    if (glfwGetKey(win, GLFW_KEY_A)) {
        x -= deltaDistance;
    }
    if (glfwGetKey(win, GLFW_KEY_D)) {
        x += deltaDistance;
    }
    
    lookAt = glm::vec3(x, y, 0.0f);
    cameraPos = glm::vec3(sinf(alpha) * cosf(theta), sinf(theta), cosf(alpha) * cosf(theta)) * distance + lookAt;
}

int main()
{
    Window window("Models", 800, 600);
    Shader shader("shader.vert", "shader.frag");
    Model model("nanosuit", "nanosuit.obj");
    
    Shader lampShader("shader.vert", "lamp.frag");
    VertexBuffer lampVbo;
    lampVbo.setBufferData(vertices, sizeof(vertices), GL_STATIC_DRAW);
    VertexArray lampVao;
    lampVao.setAttribPointer(lampVbo, 0, 3, 8, 0);
    
    glm::vec3 pointLightPositions[] = {
        glm::vec3(-1.7f, 10.2f, 5.0f),
        glm::vec3(2.3f, 2.3f, -4.0f),
        glm::vec3(-1.0f, 15.0f, 1.0f),
        glm::vec3(5.0f, 13.0f, -3.0f)
    };
    
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    
    while (!window.shouldClose()) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
        auto aspect = static_cast<float>(window.width()) / window.height();
        auto projection = glm::perspective(glm::radians(45.0f), aspect, 0.1f, 100.0f);
        
        glm::vec3 cameraPos, lookAt;
        updateCamera(window, cameraPos, lookAt);
        auto view = glm::lookAt(cameraPos, lookAt, glm::vec3(0.0, 1.0, 0.0));
    
        shader.use();
        shader.setUniform("model", glm::mat4(1.0f));
        shader.setUniform("projection", projection);
        
        shader.setUniform("view", view);
        shader.setUniform("cameraPos", cameraPos);
        shader.setUniform("material.shininess", 32.0f);
        
        shader.setUniform("directionalLight.direction", glm::vec3(0.2f, -1.0f, -0.3f));
        shader.setUniform("directionalLight.ambient", glm::vec3(0.05f));
        shader.setUniform("directionalLight.diffuse", glm::vec3(0.3f));
        shader.setUniform("directionalLight.specular", glm::vec3(0.5f));
        
        for (int i = 0; i < 4; i++) {
            shader.setUniform("pointLights[" + std::to_string(i) + "].position", pointLightPositions[i]);
            shader.setUniform("pointLights[" + std::to_string(i) + "].ambient", glm::vec3(0.2f));
            shader.setUniform("pointLights[" + std::to_string(i) + "].diffuse", glm::vec3(0.7f));
            shader.setUniform("pointLights[" + std::to_string(i) + "].specular", glm::vec3(1.0f));
            shader.setUniform("pointLights[" + std::to_string(i) + "].constant", 1.0f);
            shader.setUniform("pointLights[" + std::to_string(i) + "].linear", 0.09f);
            shader.setUniform("pointLights[" + std::to_string(i) + "].quadratic", 0.032f);
        }
        
        for (const auto &mesh : model.meshes()) {
            
            if (!mesh->diffuseMaps().empty()) {
                mesh->diffuseMaps()[0]->bind(0);
                shader.setUniform("material.diffuse", 0);
            }
            if (!mesh->specularMaps().empty()) {
                mesh->specularMaps()[0]->bind(1);
                shader.setUniform("material.specular", 1);
            }
            
            mesh->vao().bind();
            mesh->ebo().bind();
            glDrawElements(GL_TRIANGLES, mesh->indexCount(), GL_UNSIGNED_INT, nullptr);
        }
        
        lampVao.bind();
        lampShader.use();
        lampShader.setUniform("view", view);
        lampShader.setUniform("projection", projection);
        lampShader.setUniform("lightColor", glm::vec3(1.0f));
        for (auto pointLightPosition : pointLightPositions) {
            auto scale = glm::scale(glm::mat4(), glm::vec3(0.3f));
            auto translation = glm::translate(glm::mat4(), pointLightPosition);
            lampShader.setUniform("model", translation * scale);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        
        window.swapBuffers();
        glfwPollEvents();
    }
    
    return 0;
}