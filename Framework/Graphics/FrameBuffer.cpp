//
// Created by Mike Smith on 09/12/2017.
//

#include "ThirdParty/GLAD/glad.h"
#include "FrameBuffer.h"

FrameBuffer::FrameBuffer()
{
    glGenFramebuffers(1, &_id);
}

FrameBuffer::~FrameBuffer()
{
    glDeleteFramebuffers(1, &_id);
}

void FrameBuffer::bind() const
{
    glBindFramebuffer(GL_FRAMEBUFFER, _id);
}

bool FrameBuffer::complete() const
{
    bind();
    auto isComplete = (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);
    unbind();
    return isComplete;
}

void FrameBuffer::unbind() const
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

unsigned int FrameBuffer::id() const
{
    return _id;
}

void FrameBuffer::setColorBuffer(const ColorBuffer &colorBuffer, unsigned int attachment, int level)
{
    bind();
    colorBuffer.bind();
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + attachment, GL_TEXTURE_2D, colorBuffer.id(), level);
    colorBuffer.unbind();
    unbind();
}

void FrameBuffer::setRenderBuffer(const RenderBuffer &renderBuffer)
{
    bind();
    renderBuffer.bind();
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderBuffer.id());
    renderBuffer.unbind();
    unbind();
}
