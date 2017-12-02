//
// Created by Mike Smith on 16/10/2017.
//

#include "ThirdParty/GLAD/glad.h"
#include "VertexArray.h"

VertexArray::VertexArray()
{
    glGenVertexArrays(1, &_id);
}

void VertexArray::bind() const
{
    glBindVertexArray(_id);
}

VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &_id);
}
