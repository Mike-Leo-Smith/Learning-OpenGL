//
// Created by Mike Smith on 19/10/2017.
//

#ifndef LEARNING_OPENGL_CUBEMAP_H
#define LEARNING_OPENGL_CUBEMAP_H

#include "Texture.h"

class CubeMap : public Texture
{
public:
    CubeMap(std::string path, std::string extension, bool flip = false);
    ~CubeMap() override = default;
};

#endif  // LEARNING_OPENGL_CUBEMAP_H
