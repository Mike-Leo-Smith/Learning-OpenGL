//
// Created by Mike Smith on 19/10/2017.
//

#include <iostream>
#include <fstream>
#include "ThirdParty/GLAD/glad.h"
#include "ThirdParty/STB/stb_image.h"
#include "Texture.h"

std::vector<char> Texture::_loadImage(const std::string &file_name)
{
    stbi_set_flip_vertically_on_load(_flip);
    
    int width, height, channels;
    auto imgData = stbi_load(file_name.c_str(), &width, &height, &channels, 0);
    
    if (imgData == nullptr) {
        std::cerr << "Failed to load texture: " << file_name << std::endl;
        return {};
    }
    std::vector<char> pixels(imgData, imgData + width * height * channels);
    stbi_image_free(imgData);
    
    if (channels == 4) {
        _format = GL_RGBA;
    } else if (channels == 3) {
        _format = GL_RGB;
    } else {
        std::cerr << "Unsupported channels" << std::endl;
        return {};
    }
    _width = width;
    _height = height;
    return pixels;
}

Texture::Texture(unsigned int type, bool flip)
    : _type(type), _flip(flip)
{
    glGenTextures(1, &_id);
}

void Texture::bind(int unit) const
{
    if (unit >= 0) {
        glActiveTexture(static_cast<GLenum>(GL_TEXTURE0 + unit));
    }
    glBindTexture(GL_TEXTURE_2D, _id);
}

Texture::~Texture()
{
    glDeleteTextures(1, &_id);
}

unsigned int Texture::id() const
{
    return _id;
}

unsigned int Texture::type() const
{
    return _type;
}

int Texture::width() const
{
    return _width;
}

int Texture::height() const
{
    return _height;
}

unsigned int Texture::format() const
{
    return _format;
}
