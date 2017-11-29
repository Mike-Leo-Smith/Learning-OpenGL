//
// Created by Mike Smith on 28/11/2017.
//

#ifndef LEARNING_OPENGL_GLYPH_H
#define LEARNING_OPENGL_GLYPH_H

#include <freetype2/ft2build.h>
#include <freetype/freetype.h>

class Glyph
{
private:
    unsigned int _id = 0;
    int _width = 0;
    int _height = 0;
    int _bearingX = 0;
    int _bearingY = 0;
    long _advance = 0;

public:
    Glyph(FT_Face ftFace, char32_t character);
    ~Glyph();
    void bind() const;
    int width() const;
    int height() const;
    int bearingX() const;
    int bearingY() const;
    long advance() const;
    unsigned int id() const;
};

#endif  // LEARNING_OPENGL_GLYPH_H
