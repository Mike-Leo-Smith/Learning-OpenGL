//
// Created by Mike Smith on 19/10/2017.
//

#include <ThirdParty/STB/stb_image.h>
#include "ThirdParty/GLAD/glad.h"
#include "CubeMap.h"

CubeMap::CubeMap(std::string path, std::string extension, bool flip)
    : Texture(GL_TEXTURE_CUBE_MAP, flip)
{
    if (path.back() != '/') {
        path.push_back('/');
    }
    
    if (extension.front() != '.') {
        extension.insert(0, ".");
    }
    
    glBindTexture(type(), id());
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    
    constexpr const char *faces[] = { "right", "left", "top", "bottom", "back", "front" };
    auto currFaceDir = static_cast<GLenum>(GL_TEXTURE_CUBE_MAP_POSITIVE_X);
    for (auto face : faces) {
        auto pixels = _loadImage((path + face).append(extension));
        glTexImage2D(currFaceDir++, 0, format(), width(), height(), 0, format(), GL_UNSIGNED_BYTE, pixels.data());
    }
}
