#include <iostream>
#include <ThirdParty/STB/stb_image.h>
#include "ThirdParty/GLAD/glad.h"
#include "Texture2D.h"

Texture2D::Texture2D(const std::string &file_name, bool flip)
    : Texture(GL_TEXTURE_2D, flip)
{
    auto pixels = _loadImage(file_name);
    
    glBindTexture(type(), id());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    glTexImage2D(GL_TEXTURE_2D, 0, format(), width(), height(), 0, format(), GL_UNSIGNED_BYTE, pixels.data());
    glGenerateMipmap(GL_TEXTURE_2D);
}
