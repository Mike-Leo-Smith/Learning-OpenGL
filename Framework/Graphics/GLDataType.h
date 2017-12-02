//
// Created by Mike Smith on 02/12/2017.
//

#ifndef LEARNING_OPENGL_GLTYPEID_H
#define LEARNING_OPENGL_GLTYPEID_H

#include "ThirdParty/GLAD/glad.h"

template<typename T>
struct GLDataType;

template<>
struct GLDataType<int>
{
    static constexpr auto id = GL_INT;
};

template<>
struct GLDataType<unsigned int>
{
    static constexpr auto id = GL_UNSIGNED_INT;
};

template<>
struct GLDataType<float>
{
    static constexpr auto id = GL_FLOAT;
};

template<>
struct GLDataType<char>
{
    static constexpr auto id = GL_BYTE;
};

template<>
struct GLDataType<unsigned char>
{
    static constexpr auto id = GL_UNSIGNED_BYTE;
};

#endif  // LEARNING_OPENGL_GLTYPEID_H
