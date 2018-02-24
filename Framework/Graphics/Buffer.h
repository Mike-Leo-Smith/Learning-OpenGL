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
    ~Buffer() { glDeleteBuffers(1, &_id); }
    unsigned int id() const { return _id; }
    static constexpr unsigned int type() { return bufferTypeId; }
    
    void bind() const
    {
        glBindBuffer(bufferTypeId, _id);
    }
    
    void unbind() const
    {
        glBindBuffer(bufferTypeId, 0);
    }
    
    void setData(const Data *data, unsigned int size, unsigned int usage)
    {
        glBindBuffer(bufferTypeId, _id);
        glBufferData(bufferTypeId, size, data, usage);
        glBindBuffer(bufferTypeId, 0);
    }
    
    void subData(unsigned int offset, unsigned int size, const Data *data)
    {
        glBindBuffer(bufferTypeId, _id);
        glBufferSubData(bufferTypeId, offset, size, data);
        glBindBuffer(bufferTypeId, 0);
    }
};

#endif  // LEARNING_OPENGL_BUFFER_H
