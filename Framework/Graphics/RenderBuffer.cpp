//
// Created by Mike Smith on 09/12/2017.
//

#include "ThirdParty/GLAD/glad.h"
#include "RenderBuffer.h"

RenderBuffer::RenderBuffer(int width, int height)
{
    glGenRenderbuffers(1, &_id);
    bind();
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
    unbind();
}

RenderBuffer::~RenderBuffer()
{
    glDeleteRenderbuffers(1, &_id);
}

void RenderBuffer::bind() const
{
    glBindRenderbuffer(GL_RENDERBUFFER, _id);
}

void RenderBuffer::unbind() const
{
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

unsigned int RenderBuffer::id() const
{
    return _id;
}
