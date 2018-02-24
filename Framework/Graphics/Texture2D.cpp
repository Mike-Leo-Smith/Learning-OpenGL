#include <iostream>
#include <ThirdParty/STB/stb_image.h>
#include "ThirdParty/GLAD/glad.h"
#include "Texture2D.h"

Texture2D::Texture2D(const std::string &file_name, bool flip)
    : Texture(GL_TEXTURE_2D, flip)
{
    _loadPixels(_loadImage(file_name));
}

Texture2D::Texture2D(const std::vector<char> &pixels, int width, int height, int channels)
    : Texture(GL_TEXTURE_2D, true)
{
    _width = width;
    _height = height;
    _format = (channels == 3) ? GL_RGB : GL_RGBA;
    _loadPixels(pixels);
}

void Texture2D::_loadPixels(const std::vector<char> &pixels)
{
    glBindTexture(type(), id());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, format(), width(), height(), 0, format(), GL_UNSIGNED_BYTE, pixels.data());
    glGenerateMipmap(GL_TEXTURE_2D);
}

void Texture2D::subPixels(const std::vector<char> &pixels)
{
    glBindTexture(type(), id());
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width(), height(), format(), GL_UNSIGNED_BYTE, pixels.data());
    glBindTexture(type(), 0);
}
