//
// Created by Mike Smith on 18/10/2017.
//

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "ThirdParty/GLAD/glad.h"
#include "Framework/Window/Window.h"
#include "Framework/Graphics/Graphics.h"
#include "vertices.h"

void updateCamera(Window &window, glm::vec3 &cameraPos, glm::vec3 &lookAt)
{
    static auto alpha = 0.0f;
    static auto theta = 0.0f;
    static auto lastTime = 0.0f;
    static auto distance = 5.0f;
    static auto x = 0.0f;
    static auto y = 0.0f;
    
    auto currTime = static_cast<float>(glfwGetTime());
    auto timeElapsed = currTime - lastTime;
    auto deltaAngle = timeElapsed * 2.0f;
    auto deltaDistance = timeElapsed * 5.0f;
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
    Window window("Cube Maps", 800, 600);
    Shader shader("shader.vert", "shader.frag");
    CubeMap texture("skybox", "jpg");
    
    VertexBuffer skyVbo;
    skyVbo.setBufferData(vertices, sizeof(vertices), GL_STATIC_DRAW);
    
    VertexArray skyVao;
    skyVao.setAttribPointer(skyVbo, 0, 3, 5, 0);
    
    Shader boxShader("boxShader.vert", "boxShader.frag");
    Texture2D boxTexture("container.jpg");
    
    VertexArray boxVao;
    boxVao.setAttribPointer(skyVbo, 0, 3, 5, 0);
    boxVao.setAttribPointer(skyVbo, 1, 2, 5, 3);
    
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
        
        boxShader.use();
        boxTexture.bind(0);
        boxShader.setUniform("sampler", 0);
        boxShader.setUniform("model", glm::mat4());
        boxShader.setUniform("view", view);
        boxShader.setUniform("projection", projection);
        boxVao.bind();
        glDrawArrays(GL_TRIANGLES, 0, 36);
    
        shader.use();
        texture.bind(0);
        shader.setUniform("sampler", 0);
        shader.setUniform("view", glm::mat4(glm::mat3(view)));
        shader.setUniform("projection", projection);
        skyVao.bind();
        glDepthMask(GL_FALSE);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glDepthMask(GL_TRUE);
        
        window.swapBuffers();
        glfwPollEvents();
    }
}