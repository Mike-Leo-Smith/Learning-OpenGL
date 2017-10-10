#ifndef LEARNING_OPENGL_TEXTURE_H
#define LEARNING_OPENGL_TEXTURE_H

#include <string>

class Texture {
private:
    unsigned int _id;

public:
    Texture(const std::string &file_name);
    ~Texture();
    void bind(int unit = -1);
};

#endif // LEARNING_OPENGL_TEXTURE_H