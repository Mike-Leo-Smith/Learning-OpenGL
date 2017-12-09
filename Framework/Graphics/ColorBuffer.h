//
// Created by Mike Smith on 09/12/2017.
//

#ifndef LEARNING_OPENGL_COLORBUFFER_H
#define LEARNING_OPENGL_COLORBUFFER_H

#include "Texture.h"

class ColorBuffer : public Texture
{
public:
    ColorBuffer(int width, int height);
    ~ColorBuffer() override = default;
};

#endif  // LEARNING_OPENGL_COLORBUFFER_H
