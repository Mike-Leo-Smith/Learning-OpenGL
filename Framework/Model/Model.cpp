//
// Created by Mike Smith on 16/10/2017.
//

#include <string>
#include <iostream>
#include <unordered_map>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Model.h"

Model::Model(std::string path, std::string name)
{
    if (path.back() != '/') {
        path.push_back('/');
    }
    
    Assimp::Importer importer;
    auto scene = importer.ReadFile(path + name, aiProcess_Triangulate | aiProcess_GenSmoothNormals);
    if (scene == nullptr || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || scene->mRootNode == nullptr) {
        std::cerr << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
        return;
    }
    
    for (int i = 0; i < scene->mNumMaterials; i++) {
        auto material = scene->mMaterials[i];
        aiString textureName;
        for (auto j = 0u; j < material->GetTextureCount(aiTextureType_DIFFUSE); j++) {
            scene->mMaterials[i]->GetTexture(aiTextureType_DIFFUSE, j, &textureName);
            _diffuseMaps.emplace(textureName.C_Str(), std::make_shared<Texture>(path + textureName.C_Str()));
        }
        for (auto j = 0u; j < material->GetTextureCount(aiTextureType_SPECULAR); j++) {
            scene->mMaterials[i]->GetTexture(aiTextureType_SPECULAR, j, &textureName);
            _specularMaps.emplace(textureName.C_Str(), std::make_shared<Texture>(path + textureName.C_Str()));
        }
    }
    _processNode(scene->mRootNode, scene);
}

void Model::_processNode(aiNode *node, const aiScene *scene)
{
    for (int i = 0; i < node->mNumMeshes; i++) {
        _processMesh(scene->mMeshes[node->mMeshes[i]], scene);
    }
    for (int i = 0; i < node->mNumChildren; i++) {
        _processNode(node->mChildren[i], scene);
    }
}

void Model::_processMesh(aiMesh *mesh, const aiScene *scene)
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<std::shared_ptr<Texture>> diffuseMaps;
    std::vector<std::shared_ptr<Texture>> specularMaps;
    
    for (int i = 0; i < mesh->mNumVertices; i++) {
        auto &p = mesh->mVertices[i];
        auto &n = mesh->mNormals[i];
        auto &t = mesh->mTextureCoords;
        auto pos = glm::vec3(p.x, p.y, p.z);
        auto normal = glm::vec3(n.x, n.y, n.z);
        auto tex = (t[0] == nullptr) ? glm::vec2(0.0f) : glm::vec2(t[0][i].x, t[0][i].y);
        vertices.emplace_back(pos, normal, tex);
    }
    
    for (int i = 0; i < mesh->mNumFaces; i++) {
        auto &face = mesh->mFaces[i];
        for (int j = 0; j < face.mNumIndices; j++) {
            indices.emplace_back(face.mIndices[j]);
        }
    }
    
    aiString name;
    aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
    for (auto i = 0u; i < material->GetTextureCount(aiTextureType_DIFFUSE); i++) {
        material->GetTexture(aiTextureType_DIFFUSE, i, &name);
        diffuseMaps.emplace_back(_diffuseMaps.at(name.C_Str()));
    }
    
    for (auto i = 0u; i < material->GetTextureCount(aiTextureType_SPECULAR); i++) {
        material->GetTexture(aiTextureType_SPECULAR, i, &name);
        specularMaps.emplace_back(_specularMaps.at(name.C_Str()));
    }
    
    _meshes.emplace_back(std::make_shared<Mesh>(vertices, indices, diffuseMaps, specularMaps));
}

const std::vector<std::shared_ptr<Mesh>> Model::meshes() const
{
    return _meshes;
}
