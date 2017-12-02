//
// Created by Mike Smith on 02/12/2017.
//

#ifndef LEARNING_OPENGL_BUFFER_H
#define LEARNING_OPENGL_BUFFER_H

#include "GLDataType.h"

template<unsigned int GLBufferTypeId, typename DataType>
class Buffer
{
public:
    using Data = DataType;
    static constexpr auto bufferTypeId = GLBufferTypeId;
    static constexpr auto dataTypeId = GLDataType<Data>::id;
    static constexpr auto ptrDiff = sizeof(Data);

private:
    unsigned int _id;

public:
    Buffer() : _id(0) { glGenBuffers(1, &_id); }
    virtual ~Buffer() { glDeleteBuffers(1, &_id); }
    unsigned int id() const { return _id; }
    
    static constexpr unsigned int type() { return bufferTypeId; }
    
    void bind() const
    {
        glBindBuffer(bufferTypeId, _id);
    }
    
    void setData(const void *data, unsigned int size, unsigned int usage)
    {
        glBindBuffer(bufferTypeId, _id);
        glBufferData(bufferTypeId, size, data, usage);
        glBindBuffer(bufferTypeId, 0);
    }
    
    void setSubData(unsigned int offset, unsigned int size, const void *data)
    {
        glBindBuffer(bufferTypeId, _id);
        glBufferSubData(bufferTypeId, offset, size, data);
        glBindBuffer(bufferTypeId, 0);
    }
};

using VertexBuffer = Buffer<GL_ARRAY_BUFFER, float>;
using ElementBuffer = Buffer<GL_ELEMENT_ARRAY_BUFFER, unsigned int>;

#endif  // LEARNING_OPENGL_BUFFER_H
