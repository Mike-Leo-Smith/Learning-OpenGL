//
// Created by Mike Smith on 24/02/2018.
//

#include "ThirdParty/GLAD/glad.h"
#include <cmath>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include "Framework/Graphics/Graphics.h"
#include "Framework/Window/Window.h"
#include "shadow_map.h"
#include "vertices.h"

void updateCamera(Window &window, glm::vec3 &cameraPos, glm::vec3 &center)
{
    static auto alpha = 0.0f;
    static auto theta = 0.0f;
    static auto lastTime = 0.0f;
    static auto distance = 10.0f;
    static auto x = 0.0f;
    static auto y = 1.0f;
    
    auto currTime = static_cast<float>(glfwGetTime());
    auto timeElapsed = currTime - lastTime;
    auto deltaAngle = timeElapsed * 2.0f;
    auto deltaDistance = timeElapsed * 10.0f;
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
    
    center = glm::vec3(x, y, 0.0f);
    cameraPos = glm::vec3(sinf(alpha) * cosf(theta), sinf(theta), cosf(alpha) * cosf(theta)) * distance + center;
}

int main() {
    
    Window window{"Shadow Mapping", 800, 600};
    
    ShadowMap shadowMap{1024, 1024};
    Shader shadowShader{"shadow.vert", "shadow.frag"};
    
    VertexBuffer boxVertexBuffer;
    VertexArray boxVertexArray;
    
    boxVertexBuffer.setData(boxVertices, sizeof(boxVertices), GL_STATIC_DRAW);
    boxVertexArray.setAttribPointer(boxVertexBuffer, 0, 3, 8, 0);
    boxVertexArray.setAttribPointer(boxVertexBuffer, 1, 3, 8, 3);
    boxVertexArray.setAttribPointer(boxVertexBuffer, 2, 2, 8, 6);
    
    VertexBuffer planeVertexBuffer;
    VertexArray planeVertexArray;
    
    planeVertexBuffer.setData(planeVertices, sizeof(planeVertices), GL_STATIC_DRAW);
    planeVertexArray.setAttribPointer(planeVertexBuffer, 0, 3, 8, 0);
    planeVertexArray.setAttribPointer(planeVertexBuffer, 1, 3, 8, 3);
    planeVertexArray.setAttribPointer(planeVertexBuffer, 2, 2, 8, 6);
    
    Shader shader{"shader.vert", "shader.frag"};
    Texture2D boxTexture{"container.png"};
    Texture2D floorTexture{"wall.png"};
    
    glm::vec3 boxPosition1{0.0f, 1.0f, 0.0f};
    glm::vec3 boxPosition2{-2.5f, 3.0f, -2.0f};
    glm::vec3 lightDirection{-2.0f, 4.0f, -1.0f};
    
    auto modelMatrix1 = glm::translate(glm::mat4{1.0f}, boxPosition1);
    auto modelMatrix2 = glm::translate(glm::mat4{1.0f}, boxPosition2);
    
    glClearColor(0.2, 0.3, 0.4, 1.0);
    glEnable(GL_DEPTH_TEST);
    
    while (!window.shouldClose()) {
        
        // First pass: bake the shadow map.
        shadowMap.bindFramebuffer();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glViewport(0, 0, shadowMap.width(), shadowMap.height());

        auto lightSpaceMatrix = shadowMap.transform(lightDirection, glm::vec3{0.0f, 0.0f, 0.0f});

        shadowShader.use();
        shadowShader.setUniform("lightSpaceMatrix", lightSpaceMatrix);

        boxVertexArray.bind();
        shadowShader.setUniform("modelMatrix", modelMatrix1);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        shadowShader.setUniform("modelMatrix", modelMatrix2);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        planeVertexArray.bind();
        shadowShader.setUniform("modelMatrix", glm::mat4{1.0f});
        glDrawArrays(GL_TRIANGLES, 0, 6);
        
        auto windowWidth = window.width();
        auto windowHeight = window.height();
        
        // Second pass: render scene with shadow.
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glViewport(0, 0, windowWidth, windowHeight);
        
        glm::vec3 cameraPosition{0.0f, 0.0f, -3.0f};
        glm::vec3 cameraLookAt;
    
        updateCamera(window, cameraPosition, cameraLookAt);
    
        auto aspect = static_cast<float>(windowWidth) / windowHeight;
        auto projection = glm::perspective(glm::radians(45.0f), aspect, 0.1f, 100.0f);
        auto view = glm::lookAt(cameraPosition, cameraLookAt, glm::vec3{0.0f, 1.0f, 0.0f});

        shader.use();
        shader.setUniform("lightDirection", lightDirection);
        shader.setUniform("projectionMatrix", projection);
        shader.setUniform("viewMatrix", view);
        shader.setUniform("lightSpaceTransformMatrix", lightSpaceMatrix);
        shader.setUniform("cameraPosition", cameraPosition);

        shader.setUniform("diffuseSampler", 0);
        shader.setUniform("shadowSampler", 1);
        
        shadowMap.bindDepthMap(1);
    
        boxTexture.bind(0);
        boxVertexArray.bind();
        shader.setUniform("modelMatrix", modelMatrix1);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        shader.setUniform("modelMatrix", modelMatrix2);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        floorTexture.bind(0);
        planeVertexArray.bind();
        shader.setUniform("modelMatrix", glm::scale(glm::mat4{1.0f}, glm::vec3{4.0f}));
        glDrawArrays(GL_TRIANGLES, 0, 36);
        
        window.swapBuffers();
        glfwPollEvents();
    }
    
}
