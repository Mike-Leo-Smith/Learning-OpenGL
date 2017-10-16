//
// Created by Mike Smith on 16/10/2017.
//

#include "ThirdParty/GLAD/glad.h"
#include "Buffer.h"

Buffer::Buffer(unsigned int type) : _type(type)
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
