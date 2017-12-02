#ifndef LEARNING_OPENGL_TEXTURE_2D_H
#define LEARNING_OPENGL_TEXTURE_2D_H

#include <string>
#include "Texture.h"

class Texture2D : public Texture {
public:
    explicit Texture2D(const std::string &file_name, bool flip = true);
    ~Texture2D() override = default;
};

#endif // LEARNING_OPENGL_TEXTURE_2D_H
