//
// Created by Mike Smith on 16/10/2017.
//

#ifndef LEARNING_OPENGL_MODEL_H
#define LEARNING_OPENGL_MODEL_H

#include <vector>
#include <string>
#include <unordered_map>
#include <memory>
#include "Mesh.h"

class Model final
{
private:
    std::vector<std::shared_ptr<Mesh>> _meshes;
    std::unordered_map<std::string, std::shared_ptr<Texture2D>> _diffuseMaps;
    std::unordered_map<std::string, std::shared_ptr<Texture2D>> _specularMaps;
    void _processNode(struct aiNode *node, const struct aiScene *scene);
    void _processMesh(struct aiMesh *mesh, const struct aiScene *scene);
    
public:
    Model(std::string path, std::string name);
    ~Model() = default;
    const std::vector<std::shared_ptr<Mesh>> meshes() const;
};

#endif  // LEARNING_OPENGL_MODEL_H
