#ifndef LEARNING_OPENGL_TEXTURE_2D_H
#define LEARNING_OPENGL_TEXTURE_2D_H

#include <string>
#include "Texture.h"

class Texture2D: public Texture
{
protected:
    void _loadPixels(const std::vector<char> &pixels);
    
public:
    explicit Texture2D(const std::vector<char> &pixels, int width, int height, int channels);
    explicit Texture2D(const std::string &file_name, bool flip = true);
    ~Texture2D() override = default;
    
    void subPixels(const std::vector<char> &pixels);
};

#endif // LEARNING_OPENGL_TEXTURE_2D_H
