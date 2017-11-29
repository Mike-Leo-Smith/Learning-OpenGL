//
// Created by Mike Smith on 28/11/2017.
//

#ifndef LEARNING_OPENGL_TEXT_H
#define LEARNING_OPENGL_TEXT_H

#include <glm/glm.hpp>
#include "Framework/Graphics/Graphics.h"
#include "Font.h"

class Text
{
private:
    std::weak_ptr<Font> _font;
    VertexBuffer _vbo;
    VertexArray _vao;
    std::string _str;
    glm::vec4 _color;
    
    
};

#endif  // LEARNING_OPENGL_TEXT_H
