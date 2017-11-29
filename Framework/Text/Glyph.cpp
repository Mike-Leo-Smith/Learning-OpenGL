//
// Created by Mike Smith on 28/11/2017.
//

#include <iostream>
#include "ThirdParty/GLAD/glad.h"
#include "Glyph.h"

Glyph::Glyph(FT_Face ftFace, char32_t character)
{
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); //禁用字节对齐限制
    if (FT_Load_Char(ftFace, character, FT_LOAD_RENDER)) {
        std::cout << "Failed to load glyph of \'" << character << "\'..." << std::endl;
    }
    
    _width = ftFace->glyph->bitmap.width;
    _height = ftFace->glyph->bitmap.rows;
    _bearingX = ftFace->glyph->bitmap_left;
    _bearingY = ftFace->glyph->bitmap_top;
    _advance = ftFace->glyph->advance.x;
    
    auto &&buffer = ftFace->glyph->bitmap.buffer;
    
    glGenTextures(1, &_id);
    glBindTexture(GL_TEXTURE_2D, _id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, _width, _height, 0, GL_RED, GL_UNSIGNED_BYTE, buffer);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

Glyph::~Glyph()
{
    glDeleteTextures(1, &_id);
}

unsigned int Glyph::id() const
{
    return _id;
}

int Glyph::width() const
{
    return _width;
}

int Glyph::height() const
{
    return _height;
}

int Glyph::bearingX() const
{
    return _bearingX;
}

int Glyph::bearingY() const
{
    return _bearingY;
}

long Glyph::advance() const
{
    return _advance;
}

void Glyph::bind() const
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _id);
}
