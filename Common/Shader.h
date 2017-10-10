//
// Created by Mike Smith on 10/10/2017.
//

#ifndef LEARNING_OPENGL_SHADER_H
#define LEARNING_OPENGL_SHADER_H

class Shader
{
private:
    unsigned int _id = 0;

public:
    Shader(const char *vsh_file_name, const char *fsh_file_name);
    ~Shader();
    unsigned int id();
    void use();
};

#endif  // LEARNING_OPENGL_SHADER_H
