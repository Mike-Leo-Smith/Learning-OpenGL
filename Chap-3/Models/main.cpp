#include <iostream>
#include <ThirdParty/GLAD/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Framework/Window/Window.h"
#include "Framework/Graphics/Graphics.h"
#include "Framework/Model/Model.h"

glm::vec3 updateCamera(Window &window)
{
    static auto alpha = 0.0f;
    static auto theta = 0.0f;
    static auto lastTime = 0.0f;
    static auto distance = 5.0f;
    
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
        if (distance > 100.0f) {
            distance = 100.0f;
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
    Window window("Models", 800, 600);
    Shader shader("shader.vert", "shader.frag");
    Model model("Blonde Elexis - nude", "Blonde Elexis - nude.obj");
    
    std::cout << sizeof(Vertex) << std::endl;
    
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    
    auto aspect = static_cast<float>(window.width()) / window.height();
    auto projection = glm::perspective(glm::radians(45.0f), aspect, 0.1f, 100.0f);
    
    static auto x = 0.0f;
    static auto y = 0.0f;
    
    shader.use();
    shader.setUniform("model", glm::mat4(1.0f));
    shader.setUniform("projection", projection);
    
    while (!window.shouldClose()) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        auto win = window.handler();
        auto deltaDistance = 0.1f;
        
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
        
        auto cameraPos = updateCamera(window);
        auto view = glm::lookAt(cameraPos + glm::vec3(x, y, 0.0f), glm::vec3(x, y, 0.0f), glm::vec3(0.0, 1.0, 0.0));
        
        shader.setUniform("view", view);
        
        for (const auto &mesh : model.meshes()) {
            auto size = static_cast<int>(mesh->diffuseMaps().size());
            shader.setUniform("diffuseCount", size);
            for (int i = 0; i < size; i++) {
                mesh->diffuseMaps()[i]->bind(i);
                shader.setUniform("diffuse[" + std::to_string(i) + "]", i);
            }
            mesh->vao().bind();
            mesh->ebo().bind();
            glDrawElements(GL_TRIANGLES, mesh->indexCount(), GL_UNSIGNED_INT, nullptr);
        }
        window.swapBuffers();
        glfwPollEvents();
    }
    
    return 0;
}