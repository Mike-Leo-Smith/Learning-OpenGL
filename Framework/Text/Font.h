//
// Created by Mike Smith on 28/11/2017.
//

#ifndef LEARNING_OPENGL_FONT_H
#define LEARNING_OPENGL_FONT_H

#include <string>
#include <unordered_map>
#include <memory>
#include "Glyph.h"

class Font
{
private:
    mutable std::unordered_map<char32_t, std::shared_ptr<Glyph>> _glyphs;
    FT_Library _ftLibrary;
    FT_Face _ftFace;

public:
    explicit Font(const std::string &fontPath, unsigned int pixelSize = 48);
    ~Font();
    const std::shared_ptr<Glyph> &getGlyph(char32_t character) const;
};

#endif  // LEARNING_OPENGL_FONT_H
