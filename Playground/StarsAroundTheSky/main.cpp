//
// Created by Mike Smith on 05/12/2017.
//

#include <vector>
#include <iostream>
#include <random>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "ThirdParty/GLAD/glad.h"
#include "Framework/Graphics/Graphics.h"
#include "Framework/Window/Window.h"

auto generateStars(int starCount)
{
    std::random_device randomDevice;
    std::default_random_engine randomEngine(randomDevice());
    std::uniform_real_distribution<double> randomCosTheta(-1, 1);
    std::uniform_real_distribution<double> randomAlpha(-M_PI, M_PI);
    
    std::vector<float> stars;
    for (auto i = 0; i < starCount; i++) {
        auto alpha = randomAlpha(randomEngine);
        auto cosTheta = randomCosTheta(randomEngine);
        auto sinTheta = sqrt(1 - cosTheta * cosTheta);
        auto x = static_cast<float>(sinTheta * cos(alpha));
        auto y = static_cast<float>(cosTheta);
        auto z = static_cast<float>(sinTheta * sin(alpha));
        stars.push_back(x);
        stars.push_back(y);
        stars.push_back(z);
    }
    return stars;
}

int main()
{
    constexpr auto starCount = 2000;
    auto stars = generateStars(starCount);
    
    Window window("Stars around the Sky", 800, 600);
    
    VertexBuffer vbo;
    VertexArray vao;
    vbo.setData(stars.data(), static_cast<unsigned int>(starCount * 3 * sizeof(float)), GL_STATIC_DRAW);
    vao.setAttribPointer(vbo, 0, 3, 3, 0);
    
    Shader shader("shader.vert", "shader.frag");
    shader.use();
    
    glClearColor(0.1, 0.1, 0.1, 1.0);
    glPointSize(12);
    
    while (!window.shouldClose()) {
    
        auto aspect = static_cast<float>(window.width()) / window.height();
        auto projection = glm::perspective(static_cast<float>(M_PI_4), aspect, 0.1f, 100.0f);
        auto translate = glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, -3.0f));
        auto rotation = glm::rotate(glm::mat4(), static_cast<float>(M_PI / 8), glm::vec3(0.0f, 0.0f, -1.0f));
        auto view = rotation * translate;
        auto time = glfwGetTime();
        auto model = glm::rotate(glm::mat4(), static_cast<float>(cos(time) * M_PI), glm::vec3(0.0f, 1.0f, 0.0f));
        
        vao.bind();
        shader.setUniform("mvp", projection * view * model);
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glDrawArrays(GL_POINTS, 0, starCount * 3);
        
        window.swapBuffers();
        glfwPollEvents();
    }
    
    return 0;
}