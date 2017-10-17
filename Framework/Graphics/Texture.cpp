#include <iostream>
#include "ThirdParty/GLAD/glad.h"
#include "ThirdParty/STB/stb_image.h"
#include "Texture.h"

Texture::Texture(const std::string &file_name) {
    stbi_set_flip_vertically_on_load(true);

    int width, height, channels;
    auto imgData = stbi_load(file_name.c_str(), &width, &height, &channels, 0);
    
    if (imgData == nullptr) {
        std::cerr << "Failed to load texture: " << file_name << std::endl;
        return;
    }

    glGenTextures(2, &_id);
    glBindTexture(GL_TEXTURE_2D, _id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    if (channels == 4) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imgData);
    } else if (channels == 3) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, imgData);
    } else {
        std::cerr << "Unsupported channels" << std::endl;
        return;
    }
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(imgData);
}

Texture::~Texture() {
    glDeleteTextures(1, &_id);
}

void Texture::bind(int unit) const {
    if (unit >= 0) {
        glActiveTexture(static_cast<GLenum>(GL_TEXTURE0 + unit));
    }
    glBindTexture(GL_TEXTURE_2D, _id);
}
