//
// Created by Thomas Buffard on 7/15/20.
//

#ifndef COMP371_MESH_H
#define COMP371_MESH_H

#include <glm/glm.hpp>

#include "shader_m.h"

#include <string>
#include <vector>

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec3 TexCoords;
};

struct Texture {
    unsigned int id;
    std::string type;
    std::string path;
};

class Mesh {
public:
    // mesh data
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    // Mesh constructor
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);

    // Render the mesh
    void Draw(Shader &shader);
private:
    // render data
    unsigned int VAO, VBO, EBO;

    // Initializes the buffers and arrays for rendering
    void setupMesh();
};


#endif //COMP371_MESH_H
