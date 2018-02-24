//
// Created by Mike Smith on 24/02/2018.
//

#include <glm/gtc/matrix_transform.hpp>
#include "ThirdParty/GLAD/glad.h"
#include "Framework/Graphics/Graphics.h"
#include "shadow_map.h"

ShadowMap::ShadowMap(int width, int height)
    : _width{width}, _height{height}
{
    // Create the frame buffer object.
    glGenFramebuffers(1, &_framebuffer);
    
    // Create a texture as the depth buffer.
    glGenTextures(1, &_depthMap);
    glBindTexture(GL_TEXTURE_2D, _depthMap);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, _width, _height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    float borderColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
    
    // Attach the texture to the shadow map frame buffer object.
    glBindFramebuffer(GL_FRAMEBUFFER, _framebuffer);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, _depthMap, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

ShadowMap::~ShadowMap()
{
    glDeleteFramebuffers(1, &_framebuffer);
    glDeleteTextures(1, &_depthMap);
}

void ShadowMap::bindFramebuffer() const
{
    glBindFramebuffer(GL_FRAMEBUFFER, _framebuffer);
}

void ShadowMap::bindDepthMap(int unit) const
{
    glActiveTexture(static_cast<GLenum>(GL_TEXTURE0 + unit));
    glBindTexture(GL_TEXTURE_2D, _depthMap);
}

glm::mat4 ShadowMap::transform(const glm::vec3 &direction, const glm::vec3 &center) const
{
    auto projection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 1.0f, 10.0f);
    auto view = glm::lookAt(direction, center, glm::vec3{0.0f, 1.0f, 0.0f});
    return projection * view;
}

int ShadowMap::width() const
{
    return _width;
}

int ShadowMap::height() const
{
    return _height;
}
