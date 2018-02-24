//
// Created by Mike Smith on 28/11/2017.
//

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <Framework/Text/Font.h>
#include "ThirdParty/GLAD/glad.h"
#include "Framework/Window/Window.h"
#include "Framework/Graphics/Graphics.h"

int main()
{
    Window window("Stencil Testing", 800, 600);
    Shader shader("shader.vert", "shader.frag");
    
    VertexArray vao;
    VertexBuffer vbo;
    vbo.setData(nullptr, sizeof(float) * 6 * 4, GL_DYNAMIC_DRAW);
    vao.setAttribPointer(vbo, 0, 4, 4, 0);
    
    Font font1("AppleMyungjo.ttf");
    Font font2("Arial Unicode.ttf");
    Font font3("Songti.ttc");
    
    glClearColor(0.2, 0.3, 0.4, 1.0);
    
    shader.use();
    shader.setUniform("sampler", 0);
    vao.bind();
    
    glm::mat4 projection = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f);
    
    shader.setUniform("textColor", glm::vec3(0.7f, 0.9f, 0.2f));
    shader.setUniform("projection", projection);
    
    auto scale = 1.0f;
    std::wstring str = L"你好！大家好！Hello, world!";
    
    while (!window.shouldClose()) {
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        auto x = 150.0f;
        auto y = 300.0f;
        
        for (auto &&c : str) {
            auto &&font = font3;
            auto &&glyph = font.getGlyph(static_cast<char32_t>(c));
            
            GLfloat xPos = x + glyph->bearingX() * scale;
            GLfloat yPos = y - (glyph->height() - glyph->bearingY()) * scale;
    
            GLfloat w = glyph->width() * scale;
            GLfloat h = glyph->height() * scale;
            
            GLfloat vertices[6][4] = {
                { xPos, yPos + h, 0.0, 0.0 },
                { xPos, yPos, 0.0, 1.0 },
                { xPos + w, yPos, 1.0, 1.0 },
        
                { xPos, yPos + h, 0.0, 0.0 },
                { xPos + w, yPos, 1.0, 1.0 },
                { xPos + w, yPos + h, 1.0, 0.0 }
            };
            
            glyph->bind();
            vbo.subData(0, sizeof(vertices), reinterpret_cast<float *>(vertices));
            vao.bind();
            glDrawArrays(GL_TRIANGLES, 0, 6);
            
            x += (glyph->advance() >> 6) * scale; // 位偏移6个单位来获取单位为像素的值 (2^6 = 64)
        }

        window.swapBuffers();
        glfwPollEvents();
    }
    
    return 0;
}
