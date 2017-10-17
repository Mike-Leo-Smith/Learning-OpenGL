//
// Created by Mike Smith on 16/10/2017.
//

#ifndef LEARNING_OPENGL_VERTEX_BUFFER_H
#define LEARNING_OPENGL_VERTEX_BUFFER_H

#include <iostream>
#include "Buffer.h"

class VertexBuffer : public Buffer
{
public:
    VertexBuffer();
    ~VertexBuffer() override = default;
};

#endif  // LEARNING_OPENGL_VERTEX_BUFFER_H
