//
// Created by Mike Smith on 10/10/2017.
//

#ifndef LEARNING_OPENGL_SHADER_H
#define LEARNING_OPENGL_SHADER_H

#include <string>
#include "Vector.h"

class Shader
{
private:
    unsigned int _id = 0;

public:
    Shader(const char *vsh_file_name, const char *fsh_file_name);
    ~Shader();
    unsigned int id();
    void use();
    void setUniform(const std::string &name, float value);
    void setUniform(const std::string &name, const Vector2D &vector2d);
    void setUniform(const std::string &name, const Vector3D &vector3d);
    void setUniform(const std::string &name, const Vector4D &vector4d);
};

#endif  // LEARNING_OPENGL_SHADER_H
