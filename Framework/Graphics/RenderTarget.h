//
// Created by Mike Smith on 09/12/2017.
//

#ifndef LEARNING_OPENGL_RENDERTARGET_H
#define LEARNING_OPENGL_RENDERTARGET_H

#include "FrameBuffer.h"

class RenderTarget
{
private:
    FrameBuffer _frameBuffer;
    ColorBuffer _colorBuffer;
    RenderBuffer _renderBuffer;

public:
    RenderTarget(int width, int height);
    ~RenderTarget() = default;
    void bind() const;
    void unbind() const;
    const FrameBuffer &frameBuffer() const;
    const ColorBuffer &colorBuffer() const;
    const RenderBuffer &renderBuffer() const;
};

#endif  // LEARNING_OPENGL_RENDERTARGET_H
