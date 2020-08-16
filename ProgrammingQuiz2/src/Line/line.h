//
// Created by danie on 2020-07-11.
//

#ifndef COMP371_LINE_H
#define COMP371_LINE_H

#include <vector>
#include "../Utilities/shader_m.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Line {
public:
    std::vector<float> vertices;
    std::vector<unsigned int> indices;

    Line(std::vector<float> vertices, std::vector<unsigned int> indices);

    void draw(Shader &shader);

    void deleteBuffers();

private:
    unsigned int VBO, VAO, EBO;

    void setupLine();
};

#endif //COMP371_LINE_H
