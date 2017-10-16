//
// Created by Mike Smith on 16/10/2017.
//

#ifndef LEARNING_OPENGL_ARRAY_BUFFER_H
#define LEARNING_OPENGL_ARRAY_BUFFER_H

#include "Buffer.h"

class ArrayBuffer : public Buffer
{
public:
    ArrayBuffer();
    ~ArrayBuffer() override = default;
};

#endif  // LEARNING_OPENGL_ARRAY_BUFFER_H
