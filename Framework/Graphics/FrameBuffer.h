//
// Created by Mike Smith on 09/12/2017.
//

#ifndef LEARNING_OPENGL_FRAMEBUFFER_H
#define LEARNING_OPENGL_FRAMEBUFFER_H

#include "ColorBuffer.h"
#include "RenderBuffer.h"

class FrameBuffer
{
private:
    unsigned int _id;

public:
    FrameBuffer();
    ~FrameBuffer();
    void bind() const;
    void unbind() const;
    bool complete() const;
    unsigned int id() const;
    void setColorBuffer(const ColorBuffer &colorBuffer, unsigned int attachment = 0, int level = 0);
    void setRenderBuffer(const RenderBuffer &renderBuffer);
};

#endif  // LEARNING_OPENGL_FRAMEBUFFER_H
