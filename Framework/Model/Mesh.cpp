//
// Created by Mike Smith on 16/10/2017.
//

#include "ThirdParty/GLAD/glad.h"
#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices,
           std::vector<std::shared_ptr<Texture>> diff, std::vector<std::shared_ptr<Texture>> spec)
    : _vertexCount(static_cast<unsigned int>(vertices.size())),
      _indexCount(static_cast<unsigned int>(indices.size())),
      _diffuseMaps(std::move(diff)), _specularMaps(std::move(spec))
{
    _vbo.setBufferData(vertices.data(), _vertexCount * sizeof(Vertex), GL_STATIC_DRAW);
    _ebo.setBufferData(indices.data(), _indexCount * sizeof(unsigned int), GL_STATIC_DRAW);
    _vao.setAttribPointer(_vbo, 0, 3, 8, 0);
    _vao.setAttribPointer(_vbo, 1, 3, 8, 3);
    _vao.setAttribPointer(_vbo, 2, 2, 8, 6);
}

const VertexArray &Mesh::vao() const
{
    return _vao;
}

const VertexBuffer &Mesh::vbo() const
{
    return _vbo;
}

const ElementBuffer &Mesh::ebo() const
{
    return _ebo;
}

unsigned int Mesh::vertexCount() const
{
    return _vertexCount;
}

unsigned int Mesh::indexCount() const
{
    return _indexCount;
}

const std::vector<std::shared_ptr<Texture>> &Mesh::diffuseMaps() const
{
    return _diffuseMaps;
}

const std::vector<std::shared_ptr<Texture>> &Mesh::specularMaps() const
{
    return _specularMaps;
}
