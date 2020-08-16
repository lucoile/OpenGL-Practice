//
// Created by Thomas Buffard on 7/15/20.
//

#ifndef COMP371_MODEL_H
#define COMP371_MODEL_H

#include <glm/glm.hpp>

#include "shader_m.h"
#include "mesh.h"

#include <string>
#include <vector>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class Model {
public:
    // constructor, expects a filepath to a 3D model.
    Model(std::string const path);

    // draws the model
    void Draw(Shader &shader, GLenum type);
private:
    // model data
    std::vector<Mesh> meshes;
    std::string directory;

    // textures
    std::vector<LightingTexture> textures_loaded;

    // loads a model with supported ASSIMP extensions from file
    // and stores the resulting meshes in the meshes vector.
    void loadModel(std::string path);

    // processes a node in a recursive fashion.
    // Processes each individual mesh located at the node
    // and repeats this process on its children nodes (if any).
    void processNode(aiNode *node, const aiScene *scene);
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);

    // checks all material textures of a given type and loads the textures if they're not loaded yet.
    // the required info is returned as a Texture struct.
    std::vector<LightingTexture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);

    unsigned int TextureFromFile(const char *path, const std::string &directory);
};


#endif //COMP371_MODEL_H
