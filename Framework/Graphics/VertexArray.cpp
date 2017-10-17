//
// Created by Mike Smith on 16/10/2017.
//

#include "ThirdParty/GLAD/glad.h"
#include "VertexArray.h"
#include "Buffer.h"

VertexArray::VertexArray()
{
    glGenVertexArrays(1, &_id);
}

void VertexArray::bind() const
{
    glBindVertexArray(_id);
}

void VertexArray::setAttribPointer(const Buffer &buffer, unsigned int index, int size, int stride, int offset)
{
    glBindVertexArray(_id);
    glBindBuffer(buffer.type(), buffer.id());
    glEnableVertexAttribArray(index);
    glVertexAttribPointer(index, size, buffer.dataType(), GL_FALSE, stride * buffer.ptrDiff(),
                          reinterpret_cast<void *>(offset * buffer.ptrDiff()));
    glBindBuffer(buffer.type(), 0);
    glBindVertexArray(0);
}

VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &_id);
}
