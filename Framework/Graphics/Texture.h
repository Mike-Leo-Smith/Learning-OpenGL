//
// Created by Mike Smith on 19/10/2017.
//

#ifndef LEARNING_OPENGL_TEXTURE_H
#define LEARNING_OPENGL_TEXTURE_H

#include <string>
#include <vector>

class Texture
{
private:
    unsigned int _id;
    unsigned int _type;
    unsigned int _format = 0;
    bool _flip;
    int _width = 0;
    int _height = 0;
    
protected:
    std::vector<char> _loadImage(const std::string &file_name);
    
public:
    Texture(unsigned int type, bool flip);
    Texture(const Texture &) = delete;
    Texture operator=(const Texture &) = delete;
    virtual ~Texture();
    unsigned int id() const;
    unsigned int type() const;
    unsigned int format() const;
    int width() const;
    int height() const;
    void bind(int unit = -1) const;
};

#endif  // LEARNING_OPENGL_TEXTURE_H
