//
// Created by Mike Smith on 16/10/2017.
//

#include <iostream>
#include "ThirdParty/GLAD/glad.h"
#include "Buffer.h"

Buffer::Buffer(unsigned int type, unsigned int dataType, unsigned int ptrDiff)
    : _type(type), _dataType(dataType), _ptrDiff(ptrDiff)
{
    glGenBuffers(1, &_id);
}

Buffer::~Buffer()
{
    glDeleteBuffers(1, &_id);
}

unsigned int Buffer::id() const
{
    return _id;
}

unsigned int Buffer::type() const
{
    return _type;
}

void Buffer::setBufferData(const void *data, unsigned int size, unsigned int usage)
{
    glBindBuffer(GL_ARRAY_BUFFER, _id);
    glBufferData(GL_ARRAY_BUFFER, size, data, usage);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

unsigned int Buffer::dataType() const
{
    return _dataType;
}

unsigned int Buffer::ptrDiff() const
{
    return _ptrDiff;
}

void Buffer::bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _id);
}
