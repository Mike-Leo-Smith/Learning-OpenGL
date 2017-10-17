//
// Created by Mike Smith on 16/10/2017.
//

#include "ThirdParty/GLAD/glad.h"
#include "ElementBuffer.h"

ElementBuffer::ElementBuffer()
    : Buffer(GL_ELEMENT_ARRAY_BUFFER, GL_UNSIGNED_INT, sizeof(unsigned int)) {}
