//
// Created by Mike Smith on 16/10/2017.
//

#ifndef LEARNING_OPENGL_VERTEX_ARRAY_H
#define LEARNING_OPENGL_VERTEX_ARRAY_H

#include "Buffer.h"

class VertexArray
{
private:
    unsigned int _id;
    
public:
    VertexArray();
    ~VertexArray();
    void bind();
    void setAttribPointer(const Buffer &buffer, unsigned int index, int size, int stride, int offset);
};

#endif  // LEARNING_OPENGL_VERTEX_ARRAY_H
