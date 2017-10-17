//
// Created by Mike Smith on 16/10/2017.
//

#ifndef LEARNING_OPENGL_MESH_H
#define LEARNING_OPENGL_MESH_H

#include <vector>
#include <memory>
#include <Framework/Graphics/ElementBuffer.h>
#include "Framework/Graphics/Graphics.h"

class Mesh
{
private:
    VertexArray _vao;
    VertexBuffer _vbo;
    ElementBuffer _ebo;
    unsigned int _vertexCount = 0;
    unsigned int _indexCount = 0;
    std::vector<std::shared_ptr<Texture>> _diffuseMaps;
    std::vector<std::shared_ptr<Texture>> _specularMaps;

public:
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices,
         std::vector<std::shared_ptr<Texture>> diff, std::vector<std::shared_ptr<Texture>> spec);
    ~Mesh() = default;
    const VertexArray &vao() const;
    const VertexBuffer &vbo() const;
    const ElementBuffer &ebo() const;
    unsigned int vertexCount() const;
    unsigned int indexCount() const;
    const std::vector<std::shared_ptr<Texture>> &diffuseMaps() const;
    const std::vector<std::shared_ptr<Texture>> &specularMaps() const;
};

#endif  // LEARNING_OPENGL_MESH_H
