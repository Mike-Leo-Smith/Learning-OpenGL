//
// Created by Mike Smith on 24/02/2018.
//

#ifndef LEARNING_OPENGL_SHADOW_MAP_H
#define LEARNING_OPENGL_SHADOW_MAP_H

#include <glm/glm.hpp>

class ShadowMap
{
private:
    int _width = 0;
    int _height = 0;
    unsigned int _framebuffer = 0;
    unsigned int _depthMap = 0;
    glm::mat4 _transform;

public:
    explicit ShadowMap(int width = 1024, int height = 1024);
    ~ShadowMap();
    int width() const;
    int height() const;
    void bindFramebuffer() const;
    void bindDepthMap(int unit = 0) const;
    glm::mat4 transform(const glm::vec3 &direction, const glm::vec3 &center) const;
};

#endif  // LEARNING_OPENGL_SHADOW_MAP_H
