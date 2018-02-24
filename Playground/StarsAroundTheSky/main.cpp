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
    stars.reserve(starCount * 3 * sizeof(float));
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

auto generate_cylinder(float radius, float height, float text_proportion)
{
    constexpr auto step_count = 64;
    
    auto half_height = height / 2;
    auto step = static_cast<float>(M_PI * 2 * text_proportion / step_count);
    
    std::vector<float> cylinder;
    cylinder.reserve((step_count + 1) * 2 * 5 * sizeof(float));
    for (auto alpha_step = 0; alpha_step <= step_count; alpha_step++) {
        auto x = radius * cosf(alpha_step * step);
        auto z = radius * sinf(alpha_step * step);
        auto tex_x = alpha_step / static_cast<float>(step_count);
        
        cylinder.emplace_back(x);
        cylinder.emplace_back(half_height);
        cylinder.emplace_back(z);
        cylinder.emplace_back(1 - tex_x);
        cylinder.emplace_back(0.0f);
        
        cylinder.emplace_back(x);
        cylinder.emplace_back(-half_height);
        cylinder.emplace_back(z);
        cylinder.emplace_back(1 - tex_x);
        cylinder.emplace_back(1.0f);
    }
    
    return cylinder;
}

int main()
{
    constexpr auto starCount = 2000;
    constexpr auto text_proportion = 0.75f;
    auto stars = generateStars(starCount);
    auto cylinder = generate_cylinder(1.2f, 1.0f, text_proportion);
    
    Window window("Hello, World!", 800, 600);
    
    VertexBuffer vbo;
    VertexArray vao;
    vbo.setData(stars.data(), static_cast<unsigned int>(starCount * 3 * sizeof(float)), GL_STATIC_DRAW);
    vao.setAttribPointer(vbo, 0, 3, 3, 0);
    
    VertexBuffer cylinder_vbo;
    VertexArray cylinder_vao;
    cylinder_vbo.setData(cylinder.data(), static_cast<unsigned int>(cylinder.size() * sizeof(float)), GL_STATIC_DRAW);
    cylinder_vao.setAttribPointer(cylinder_vbo, 0, 3, 5, 0);
    cylinder_vao.setAttribPointer(cylinder_vbo, 1, 2, 5, 3);
    
    Shader shader("shader.vert", "shader.frag");
    Shader cylinder_shader{"cylinder.vert", "cylinder.frag"};
    
    Texture2D texture{"stripe.png", false};
    
    glClearColor(0.1, 0.1, 0.1, 1.0);
    glPointSize(12);
    
    while (!window.shouldClose()) {
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        auto aspect = static_cast<float>(window.width()) / window.height();
        auto projection = glm::perspective(static_cast<float>(M_PI_4), aspect, 0.1f, 100.0f);
        auto translation = glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, -3.0f));
        auto view = translation;
        auto time = glfwGetTime();
        auto model = glm::rotate(
            glm::mat4(),
            static_cast<float>(cos(time) * M_PI + M_PI * text_proportion),
            glm::vec3(0.0f, 1.0f, 0.0f));
        auto mvp = projection * view * model;
        
        shader.use();
        vao.bind();
        shader.setUniform("mvp", mvp);
        glDrawArrays(GL_POINTS, 0, starCount * 3);
        
        cylinder_shader.use();
        cylinder_vao.bind();
        texture.bind();
        cylinder_shader.setUniform("mvp", mvp);
        cylinder_shader.setUniform("sampler", 0);
        cylinder_shader.setUniform("color", glm::vec4{1.0});
        glDrawArrays(GL_TRIANGLE_STRIP, 0, static_cast<int>(cylinder.size() / 5));
        
        window.swapBuffers();
        glfwPollEvents();
    }
    
    return 0;
}