//
// Created by Mike Smith on 09/12/2017.
//

#include "ThirdParty/GLAD/glad.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include "Framework/Graphics/Graphics.h"
#include "Framework/Window/Window.h"
#include "vertices.h"

int main()
{
    constexpr auto frameWidth = 1200;
    constexpr auto frameHeight = 900;
    
    Window window("Frame Buffers", 800, 600);
    RenderTarget renderTarget(frameWidth, frameHeight);
    
    Shader shader("shader.vert", "shader.frag");
    Shader screenShader("screen_shader.vert", "screen_shader.frag");
    
    VertexBuffer boxVbo;
    VertexArray boxVao;
    boxVbo.setData(boxVertices, sizeof(boxVertices), GL_STATIC_DRAW);
    boxVao.setAttribPointer(boxVbo, 0, 3, 5, 0);
    boxVao.setAttribPointer(boxVbo, 1, 2, 5, 3);
    
    VertexBuffer floorVbo;
    VertexArray floorVao;
    floorVbo.setData(planeVertices, sizeof(planeVertices), GL_STATIC_DRAW);
    floorVao.setAttribPointer(floorVbo, 0, 3, 5, 0);
    floorVao.setAttribPointer(floorVbo, 1, 2, 5, 3);
    
    VertexBuffer screenVbo;
    VertexArray screenVao;
    screenVbo.setData(quadVertices, sizeof(quadVertices), GL_STATIC_DRAW);
    screenVao.setAttribPointer(screenVbo, 0, 2, 4, 0);
    screenVao.setAttribPointer(screenVbo, 1, 2, 4, 2);
    
    Texture2D boxTexture("container.png");
    Texture2D floorTexture("metal.png");
    
    while (!window.shouldClose()) {
        
        renderTarget.bind();
        glEnable(GL_DEPTH_TEST);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glViewport(0, 0, frameWidth, frameHeight);
        auto view = glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, -6.0f));
        auto proj = glm::perspective(glm::radians(45.0f), static_cast<float>(frameWidth) / frameHeight, 0.1f, 100.0f);
        
        shader.use();
        shader.setUniform("sampler", 0);
        
        boxVao.bind();
        boxTexture.bind();
        auto boxPos1 = glm::translate(glm::mat4(), glm::vec3(-1.0f, 0.0f, -1.0f));
        shader.setUniform("mvp", proj * view * boxPos1);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        auto boxPos2 = glm::translate(glm::mat4(), glm::vec3(2.0f, 0.0f, 0.0f));
        shader.setUniform("mvp", proj * view * boxPos2);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        
        floorVao.bind();
        floorTexture.bind();
        shader.setUniform("mvp", proj * view);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        
        renderTarget.unbind();
        glDisable(GL_DEPTH_TEST);
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glViewport(0, 0, window.width(), window.height());
        
        screenShader.use();
        screenShader.setUniform("sampler", 0);
        screenVao.bind();
        renderTarget.colorBuffer().bind();
        glDrawArrays(GL_TRIANGLES, 0, 6);
        
        window.swapBuffers();
        glfwPollEvents();
    }
    
    return 0;
}