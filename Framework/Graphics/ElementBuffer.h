//
// Created by Mike Smith on 16/10/2017.
//

#ifndef LEARNING_OPENGL_ELEMENT_BUFFER_H
#define LEARNING_OPENGL_ELEMENT_BUFFER_H

#include "Buffer.h"

class ElementBuffer : public Buffer
{
public:
    ElementBuffer();
    ~ElementBuffer() override = default;
};

#endif  // LEARNING_OPENGL_ELEMENT_BUFFER_H
