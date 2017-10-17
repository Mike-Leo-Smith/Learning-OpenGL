//
// Created by Mike Smith on 16/10/2017.
//

#include "ThirdParty/GLAD/glad.h"
#include "VertexBuffer.h"

VertexBuffer::VertexBuffer()
    : Buffer(GL_ARRAY_BUFFER, GL_FLOAT, sizeof(float)) {}
