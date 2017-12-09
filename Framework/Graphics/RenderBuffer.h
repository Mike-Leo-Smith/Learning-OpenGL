//
// Created by Mike Smith on 09/12/2017.
//

#ifndef LEARNING_OPENGL_RENDERBUFFER_H
#define LEARNING_OPENGL_RENDERBUFFER_H

class RenderBuffer
{
private:
    unsigned int _id;

public:
    RenderBuffer(int width, int height);
    ~RenderBuffer();
    void bind() const;
    void unbind() const;
    unsigned int id() const;
};

#endif  // LEARNING_OPENGL_RENDERBUFFER_H
