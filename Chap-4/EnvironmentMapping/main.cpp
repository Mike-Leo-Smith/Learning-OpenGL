//
// Created by Mike Smith on 18/10/2017.
//

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "ThirdParty/GLAD/glad.h"
#include "Framework/Graphics/Graphics.h"
#include "Framework/Model/Model.h"
#include "Framework/Window/Window.h"
#include "vertices.h"

void updateCamera(Window &window, glm::vec3 &cameraPos, glm::vec3 &lookAt)
{
    static auto alpha = 0.0f;
    static auto theta = 0.0f;
    static auto lastTime = 0.0f;
    static auto distance = 15.0f;
    static auto x = 0.0f;
    static auto y = 0.0f;
    
    auto currTime = static_cast<float>(glfwGetTime());
    auto timeElapsed = currTime - lastTime;
    auto deltaAngle = timeElapsed * 2.0f;
    auto deltaDistance = timeElapsed * 5.0f;
    lastTime = currTime;
    
    std::cout << "FPS: " << 1 / timeElapsed << std::endl;
    
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
        if (distance < 0.01f) {
            distance = 0.01f;
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
    Window window("Environment Mapping", 800, 600);
    Shader skyShader("skybox_shader.vert", "skybox_shader.frag");
    CubeMap skyTexture("skybox", "jpg");
    
    VertexBuffer boxVbo;
    boxVbo.setBufferData(vertices, sizeof(vertices), GL_STATIC_DRAW);
    
    VertexArray skyVao;
    skyVao.setAttribPointer(boxVbo, 0, 3, 8, 0);
    
    Shader reflectionShader("shader.vert", "reflection_shader.frag");
    Shader refractionShader("shader.vert", "refraction_shader.frag");
    
    VertexArray boxVao;
    boxVao.setAttribPointer(boxVbo, 0, 3, 8, 0);
    boxVao.setAttribPointer(boxVbo, 1, 3, 8, 3);
    
    Model model("nanosuit", "nanosuit.obj");
    
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glDepthFunc(GL_LEQUAL);
    
    while (!window.shouldClose()) {
        
        glEnable(GL_DEPTH_TEST);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        glm::vec3 cameraPos, lookAt;
        updateCamera(window, cameraPos, lookAt);
        auto view = glm::lookAt(cameraPos, lookAt, glm::vec3(0.0, 1.0, 0.0));
        
        auto aspect = static_cast<float>(window.width()) / window.height();
        auto projection = glm::perspective(glm::radians(45.0f), aspect, 0.1f, 100.0f);
        
        skyTexture.bind(0);
        reflectionShader.use();
        reflectionShader.setUniform("sampler", 0);
        reflectionShader.setUniform("model", glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, 3.0f)));
        reflectionShader.setUniform("view", view);
        reflectionShader.setUniform("projection", projection);
        reflectionShader.setUniform("cameraPosition", cameraPos);
        boxVao.bind();
        glDrawArrays(GL_TRIANGLES, 0, 36);
        
        reflectionShader.setUniform("model", glm::translate(glm::mat4(), glm::vec3(3.6f, -12.0f, 0.0f)));
        for (const auto &mesh : model.meshes()) {
            mesh->vao().bind();
            mesh->ebo().bind();
            glDrawElements(GL_TRIANGLES, mesh->indexCount(), GL_UNSIGNED_INT, nullptr);
        }
    
        skyTexture.bind(0);
        refractionShader.use();
        refractionShader.setUniform("sampler", 0);
        refractionShader.setUniform("view", view);
        refractionShader.setUniform("projection", projection);
        refractionShader.setUniform("cameraPosition", cameraPos);
        refractionShader.setUniform("model", glm::translate(glm::mat4(), glm::vec3(-3.6f, -12.0f, 0.0f)));
        for (const auto &mesh : model.meshes()) {
            mesh->vao().bind();
            mesh->ebo().bind();
            glDrawElements(GL_TRIANGLES, mesh->indexCount(), GL_UNSIGNED_INT, nullptr);
        }
    
        skyShader.use();
        skyTexture.bind(0);
        skyShader.setUniform("sampler", 0);
        skyShader.setUniform("view", glm::mat4(glm::mat3(view)));
        skyShader.setUniform("projection", projection);
        skyVao.bind();
        glDepthMask(GL_FALSE);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glDepthMask(GL_TRUE);
        
        window.swapBuffers();
        glfwPollEvents();
    }
}