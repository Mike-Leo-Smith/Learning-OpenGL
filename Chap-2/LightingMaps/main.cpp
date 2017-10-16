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
    static float alpha = 0;
    static float theta = 0;
    static float lastTime = 0;
    
    auto currTime = static_cast<float>(glfwGetTime());
    auto timeElapsed = currTime - lastTime;
    auto deltaAngle = timeElapsed * 2.0f;
    lastTime = currTime;
    
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
    
    return glm::vec3(sinf(alpha) * cosf(theta), sinf(theta), cosf(alpha) * cosf(theta)) * 4.0f;
}

int main()
{
    Window window("Lighting Maps", 800, 600);
    Shader boxShader("box.vert", "box.frag");
    Shader lightShader("box.vert", "light.frag");
    Texture diffuseTexture("container.png");
    Texture specularTexture("container_specular_color.png");
    
    glClearColor(0.1, 0.1, 0.1, 1.0);
    
    ArrayBuffer boxVbo;
    boxVbo.setBufferData(vertices, sizeof(vertices), GL_STATIC_DRAW);
    
    VertexArray boxVao;
    boxVao.setAttribPointer(boxVbo, 0, 3, 8, 0);
    boxVao.setAttribPointer(boxVbo, 1, 3, 8, 3);
    boxVao.setAttribPointer(boxVbo, 2, 2, 8, 6);
    
    VertexArray lightVao;
    lightVao.setAttribPointer(boxVbo, 0, 3, 8, 0);
    
    auto boxModel = glm::mat4();
    auto lightPos = glm::vec3(1.5f, 1.0f, 2.0f);
    auto lightModel = glm::scale(glm::translate(glm::mat4(), lightPos), glm::vec3(0.2f));
    auto projection = glm::perspective(glm::radians(45.0f),
                                       static_cast<float>(window.width()) / window.height(), 0.1f, 100.0f);
    
    while (!window.shouldClose()) {
        
        auto cameraPos = updateCamera(window);
        auto view = glm::lookAt(cameraPos, glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        auto lightSpecular = glm::vec3(1.0f);
        auto lightDiffuse = lightSpecular * 0.5f;
        auto lightAmbient = lightSpecular * 0.2f;
        
        boxVao.bind();
        boxShader.use();
        boxShader.setUniform("model", boxModel);
        boxShader.setUniform("view", view);
        boxShader.setUniform("projection", projection);
        boxShader.setUniform("cameraPos", cameraPos);
        boxShader.setUniform("material.shininess", 32.0f);
        boxShader.setUniform("light.position", lightPos);
        boxShader.setUniform("light.ambient", lightAmbient);
        boxShader.setUniform("light.diffuse", lightDiffuse);
        boxShader.setUniform("light.specular", lightSpecular);
        boxShader.setUniform("material.diffuse", 0);
        boxShader.setUniform("material.specular", 1);
        diffuseTexture.bind(0);
        specularTexture.bind(1);
        
        glDrawArrays(GL_TRIANGLES, 0, 36);
        
        lightVao.bind();
        lightShader.use();
        lightShader.use();
        lightShader.setUniform("model", lightModel);
        lightShader.setUniform("view", view);
        lightShader.setUniform("projection", projection);
        lightShader.setUniform("lightColor", lightSpecular);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        
        window.swapBuffers();
        glfwPollEvents();
    }
    
    return 0;
}