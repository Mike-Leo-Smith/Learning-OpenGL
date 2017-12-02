//
// Created by Mike Smith on 16/10/2017.
//

#ifndef LEARNING_OPENGL_VERTEX_ARRAY_H
#define LEARNING_OPENGL_VERTEX_ARRAY_H

#include "ThirdParty/GLAD/glad.h"

class VertexArray final
{
private:
    unsigned int _id;
    
public:
    VertexArray();
    ~VertexArray();
    void bind() const;
    
    template<typename BufferType>
    void setAttribPointer(const BufferType &buffer, unsigned int index, int size, int stride, int offset)
    {
        glBindVertexArray(_id);
        glBindBuffer(BufferType::bufferTypeId, buffer.id());
        glEnableVertexAttribArray(index);
        glVertexAttribPointer(index, size, BufferType::dataTypeId, GL_FALSE, stride * BufferType::ptrDiff,
                              static_cast<typename BufferType::Data *>(nullptr) + offset);
        glBindBuffer(buffer.type(), 0);
        glBindVertexArray(0);
    }
};

#endif  // LEARNING_OPENGL_VERTEX_ARRAY_H
