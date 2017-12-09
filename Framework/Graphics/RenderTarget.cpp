//
// Created by Mike Smith on 09/12/2017.
//

#include "RenderTarget.h"

RenderTarget::RenderTarget(int width, int height)
    : _colorBuffer(width, height), _renderBuffer(width, height)
{
    _frameBuffer.setColorBuffer(_colorBuffer);
    _frameBuffer.setRenderBuffer(_renderBuffer);
}

void RenderTarget::bind() const
{
    _frameBuffer.bind();
}

void RenderTarget::unbind() const
{
    _frameBuffer.unbind();
}

const FrameBuffer &RenderTarget::frameBuffer() const
{
    return _frameBuffer;
}

const ColorBuffer &RenderTarget::colorBuffer() const
{
    return _colorBuffer;
}

const RenderBuffer &RenderTarget::renderBuffer() const
{
    return _renderBuffer;
}
