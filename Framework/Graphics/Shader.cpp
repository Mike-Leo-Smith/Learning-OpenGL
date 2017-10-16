//
// Created by Mike Smith on 10/10/2017.
//

#include <fstream>
#include <iostream>
#include <sstream>
#include <glm/gtc/type_ptr.hpp>

#include "ThirdParty/GLAD/glad.h"
#include "Shader.h"

Shader::Shader(const char *vsh_file_name, const char *fsh_file_name) {
    GLint success;
    GLchar info[512];

    std::fstream vsh_file;
    std::stringstream vsh_stream;
    std::string vsh_source;
    const char *vsh_source_ptr = nullptr;

    vsh_file.open(vsh_file_name);
    vsh_stream << vsh_file.rdbuf();
    vsh_source = vsh_stream.str();
    vsh_source_ptr = vsh_source.c_str();

    GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vsh_source_ptr, nullptr);
    glCompileShader(vertex_shader);

    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertex_shader, 512, nullptr, info);
        std::cerr << info << std::endl;
    }

    std::fstream fsh_file;
    std::stringstream fsh_stream;
    std::string fsh_source;
    const char *fsh_source_ptr = nullptr;

    fsh_file.open(fsh_file_name);
    fsh_stream << fsh_file.rdbuf();
    fsh_source = fsh_stream.str();
    fsh_source_ptr = fsh_source.c_str();

    GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fsh_source_ptr, nullptr);
    glCompileShader(fragment_shader);

    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragment_shader, 512, nullptr, info);
        std::cerr << info << std::endl;
    }

    glDeleteProgram(_id);
    _id = glCreateProgram();
    glAttachShader(_id, vertex_shader);
    glAttachShader(_id, fragment_shader);
    glLinkProgram(_id);

    glGetProgramiv(_id, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(_id, 512, nullptr, info);
        std::cerr << info << std::endl;
    }

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
}

Shader::~Shader() { glDeleteProgram(_id); }

unsigned int Shader::id() { return _id; }

void Shader::use() { glUseProgram(_id); }

void Shader::setUniform(const std::string &name, float value) {
    glUniform1f(getUniform(name), value);
}

void Shader::setUniform(const std::string &name, int value)
{
    glUniform1i(getUniform(name), value);
}

void Shader::setUniform(const std::string &name, const Vector2 &vector2d) {
    glUniform2f(getUniform(name), vector2d.x, vector2d.y);
}

void Shader::setUniform(const std::string &name, const glm::vec2 &vec2)
{
    glUniform2f(getUniform(name), vec2.x, vec2.y);
}

void Shader::setUniform(const std::string &name, const glm::vec3 &vec3)
{
    glUniform3f(getUniform(name), vec3.x, vec3.y, vec3.z);
}

void Shader::setUniform(const std::string &name, const glm::vec4 &vec4)
{
    glUniform4f(getUniform(name), vec4.x, vec4.y, vec4.z, vec4.w);
}

void Shader::setUniform(const std::string &name, const glm::mat3 &mat3)
{
    glUniformMatrix3fv(getUniform(name), 1, GL_FALSE, glm::value_ptr(mat3));
}

void Shader::setUniform(const std::string &name, const glm::mat4 &mat4)
{
    glUniformMatrix4fv(getUniform(name), 1, GL_FALSE, glm::value_ptr(mat4));
}

int Shader::getUniform(const std::string &name)
{
    return glGetUniformLocation(_id, name.c_str());
}

void Shader::setUniform(const std::string &name, const Vector3 &vector3d) {
    glUniform3f(getUniform(name), vector3d.x, vector3d.y, vector3d.z);
}

void Shader::setUniform(const std::string &name, const Vector4 &vector4d) {
    glUniform4f(getUniform(name), vector4d.x, vector4d.y, vector4d.z, vector4d.w);
}