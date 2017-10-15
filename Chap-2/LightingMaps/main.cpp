#include <iostream>
#include <ThirdParty/GLAD/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Framework/Window/Window.h"
#include "Framework/Graphics/Shader.h"
#include "Framework/Graphics/Texture.h"

int main()
{
    Window window("Lighting Maps", 800, 600);
    Shader boxShader("box.vert", "box.frag");
    Shader lightShader("box.vert", "light.frag");
    Texture diffuseTexture("container.png");
    Texture specularTexture("container_specular_color.png");
    
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
    
    unsigned int boxVao;
    glGenVertexArrays(1, &boxVao);
    glBindVertexArray(boxVao);
    
    float vertices[] = {
        // positions      // normals    // texture coords
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
        0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
        
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        
        -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        
        -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
        0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
        
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f
    };
    
    unsigned int boxVbo;
    glGenBuffers(1, &boxVbo);
    glBindBuffer(GL_ARRAY_BUFFER, boxVbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), static_cast<float *>(nullptr) + 3);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), static_cast<float *>(nullptr) + 6);
    glEnableVertexAttribArray(2);
    
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    unsigned int lightVao;
    glGenVertexArrays(1, &lightVao);
    glBindVertexArray(lightVao);
    
    glBindBuffer(GL_ARRAY_BUFFER, boxVbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);
    
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
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
        
        auto lightSpecular = glm::vec3(1.0f);
        auto lightDiffuse = lightSpecular * 0.5f;
        auto lightAmbient = lightSpecular * 0.2f;
        
        glBindVertexArray(boxVao);
        boxShader.use();
        auto loc = glGetUniformLocation(boxShader.id(), "model");
        glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(boxModel));
        loc = glGetUniformLocation(boxShader.id(), "view");
        glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(view));
        loc = glGetUniformLocation(boxShader.id(), "projection");
        glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(projection));
        loc = glGetUniformLocation(boxShader.id(), "cameraPos");
        glUniform3fv(loc, 1, glm::value_ptr(cameraPos));
        loc = glGetUniformLocation(boxShader.id(), "material.specular");
        glUniform3f(loc, 0.5f, 0.5f, 0.5f);
        loc = glGetUniformLocation(boxShader.id(), "material.shininess");
        glUniform1f(loc, 32.0f);
        loc = glGetUniformLocation(boxShader.id(), "light.position");
        glUniform3fv(loc, 1, glm::value_ptr(lightPos));
        loc = glGetUniformLocation(boxShader.id(), "light.ambient");
        glUniform3fv(loc, 1, glm::value_ptr(lightAmbient));
        loc = glGetUniformLocation(boxShader.id(), "light.diffuse");
        glUniform3fv(loc, 1, glm::value_ptr(lightDiffuse));
        loc = glGetUniformLocation(boxShader.id(), "light.specular");
        glUniform3fv(loc, 1, glm::value_ptr(lightSpecular));
        diffuseTexture.bind(0);
        boxShader.setUniform("material.diffuse", 0);
        specularTexture.bind(1);
        boxShader.setUniform("material.specular", 1);
        
        glDrawArrays(GL_TRIANGLES, 0, 36);
        
        glBindVertexArray(lightVao);
        lightShader.use();
        loc = glGetUniformLocation(lightShader.id(), "model");
        glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(lightModel));
        loc = glGetUniformLocation(lightShader.id(), "view");
        glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(view));
        loc = glGetUniformLocation(lightShader.id(), "projection");
        glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(projection));
        loc = glGetUniformLocation(lightShader.id(), "lightColor");
        glUniform3fv(loc, 1, glm::value_ptr(lightSpecular));
        glDrawArrays(GL_TRIANGLES, 0, 36);
        
        window.swapBuffers();
        glfwPollEvents();
    }
    
    glDeleteVertexArrays(1, &boxVao);
    glDeleteBuffers(1, &boxVbo);
    
    return 0;
}