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
    Window window("Phong Lighting", 800, 600);
    Shader boxShader("box.vert", "box.frag");
    Shader lightShader("box.vert", "light.frag");
    
    float alpha = 0;
    float theta = 0;
    float lastTime = 0;
    float timeElapsed = 0;
    
    auto processKey = [&alpha, &theta, &lastTime, &timeElapsed, &window] {
        
        auto deltaAngle = timeElapsed * 2.0f;
        
        auto currentTime = static_cast<float>(glfwGetTime());
        timeElapsed = currentTime - lastTime;
        lastTime = currentTime;
        
        auto win = window.handler();
        
        if (glfwGetKey(win, GLFW_KEY_UP)) {
            theta += deltaAngle;
            if (theta > M_PI_2 - 0.05) {
                theta = static_cast<float>(M_PI_2 - 0.05);
            }
        } else if (glfwGetKey(win, GLFW_KEY_DOWN)) {
            theta -= deltaAngle;
            if (theta < -M_PI_2 + 0.05) {
                theta = static_cast<float>(-M_PI_2 + 0.05);
            }
        } else if (glfwGetKey(win, GLFW_KEY_LEFT)) {
            alpha -= deltaAngle;
        } else if (glfwGetKey(win, GLFW_KEY_RIGHT)) {
            alpha += deltaAngle;
        }
    };
    
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
        processKey();
        
        auto cameraPos = glm::vec3(sinf(alpha) * cosf(theta), sinf(theta), cosf(alpha) * cosf(theta)) * 4.0f;
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