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
    
    auto win = window.handle();
    
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
    Window window("Stencil Testing", 800, 600);
    Shader boxShader("shader.vert", "shader.frag");
    Shader frameShader("shader.vert", "single_color.frag");
    Texture2D texture("container.jpg");
    
    VertexBuffer boxVbo;
    boxVbo.setData(vertices, sizeof(vertices), GL_STATIC_DRAW);
    
    VertexArray boxVao;
    boxVao.setAttribPointer(boxVbo, 0, 3, 5, 0);
    boxVao.setAttribPointer(boxVbo, 1, 2, 5, 3);
    
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glEnable(GL_STENCIL_TEST);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

    auto aspect = static_cast<float>(window.width()) / window.height();
    auto projection = glm::perspective(glm::radians(45.0f), aspect, 0.1f, 100.0f);
    
    while (!window.shouldClose()) {
    
        glEnable(GL_DEPTH_TEST);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    
        glm::vec3 cameraPos, lookAt;
        updateCamera(window, cameraPos, lookAt);
        auto view = glm::lookAt(cameraPos, lookAt, glm::vec3(0.0, 1.0, 0.0));
        
        // Render Pass 1.
        glStencilFunc(GL_ALWAYS, 1, 0xff);
        glEnable(GL_DEPTH_TEST);
        
        boxVao.bind();
        texture.bind(0);
        boxShader.use();
        boxShader.setUniform("sampler", 0);
        boxShader.setUniform("projection", projection);
        boxShader.setUniform("view", view);
        boxShader.setUniform("model", glm::mat4());
        glDrawArrays(GL_TRIANGLES, 0, 36);
        boxShader.setUniform("model", glm::translate(glm::mat4(), glm::vec3(1.0f, 0.0f, 1.0f)));
        glDrawArrays(GL_TRIANGLES, 0, 36);
        
        // Render Pass 2.
        glStencilFunc(GL_NOTEQUAL, 1, 0xff);
        glDisable(GL_DEPTH_TEST);

        boxVao.bind();
        frameShader.use();
        frameShader.setUniform("projection", projection);
        frameShader.setUniform("view", view);
        frameShader.setUniform("model", glm::scale(glm::mat4(), glm::vec3(1.1f, 1.1f, 1.1f)));
        glDrawArrays(GL_TRIANGLES, 0, 36);
        boxShader.setUniform("model", glm::translate(glm::mat4(), glm::vec3(1.0f, 0.0f, 1.0f))
            * glm::scale(glm::mat4(), glm::vec3(1.1f, 1.1f, 1.1f)));
        glDrawArrays(GL_TRIANGLES, 0, 36);
        
        window.swapBuffers();
        glfwPollEvents();
    }
}