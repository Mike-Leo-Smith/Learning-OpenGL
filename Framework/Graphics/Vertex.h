//
// Created by Mike Smith on 16/10/2017.
//

#ifndef LEARNING_OPENGL_VERTEX_H
#define LEARNING_OPENGL_VERTEX_H

#include <glm/glm.hpp>

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoord;
    Vertex(const glm::vec3 &p, const glm::vec3 &n, const glm::vec2 &t)
        : position(p), normal(n), texCoord(t) {}
};

#endif  // LEARNING_OPENGL_VERTEX_H
