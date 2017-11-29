//
// Created by Mike Smith on 28/11/2017.
//

#include <iostream>
#include "Font.h"

Font::Font(const std::string &fontPath, unsigned int pixelSize)
{
    if (FT_Init_FreeType(&_ftLibrary)) {
        std::cerr << "Failed to initialize FreeType..." << std::endl;
    }
    if (FT_New_Face(_ftLibrary, fontPath.c_str(), 0, &_ftFace)) {
        std::cerr << "Failed to load font from \'" << fontPath << "\'..." << std::endl;
    }
    
    FT_Set_Pixel_Sizes(_ftFace, 0, pixelSize);
}

Font::~Font()
{
    FT_Done_Face(_ftFace);
    FT_Done_FreeType(_ftLibrary);
}

const std::shared_ptr<Glyph> &Font::getGlyph(char32_t character) const
{
    if (_glyphs.count(character) == 0) {
        _glyphs.emplace(character, std::make_shared<Glyph>(_ftFace, character));
    }
    return _glyphs.at(character);
}
