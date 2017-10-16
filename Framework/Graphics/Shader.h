//
// Created by Mike Smith on 10/10/2017.
//

#ifndef LEARNING_OPENGL_SHADER_H
#define LEARNING_OPENGL_SHADER_H

#include <string>
#include <glm/glm.hpp>
#include "Framework/Mathematics/Vector.h"

class Shader
{
private:
    unsigned int _id = 0;

public:
    Shader(const char *vsh_file_name, const char *fsh_file_name);
    ~Shader();
    unsigned int id();
    void use();
    int getUniform(const std::string &name);
    void setUniform(const std::string &name, int value);
    void setUniform(const std::string &name, float value);
    void setUniform(const std::string &name, const Vector2 &vector2d);
    void setUniform(const std::string &name, const Vector3 &vector3d);
    void setUniform(const std::string &name, const Vector4 &vector4d);
    void setUniform(const std::string &name, const glm::vec2 &vec2);
    void setUniform(const std::string &name, const glm::vec3 &vec3);
    void setUniform(const std::string &name, const glm::vec4 &vec4);
    void setUniform(const std::string &name, const glm::mat3 &mat3);
    void setUniform(const std::string &name, const glm::mat4 &mat4);
};

#endif  // LEARNING_OPENGL_SHADER_H
