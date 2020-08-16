//
// Created by danie on 2020-07-11.
//

#include "line.h"

Line::Line(std::vector<float> vertices, std::vector<unsigned int> indices) {
    this->vertices = vertices;
    this->indices = indices;

    setupLine();
}

void Line::draw(Shader &shader) {
    glBindVertexArray(VAO);
    glDrawElements(GL_LINES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Line::deleteBuffers() {
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &VAO);
    glDeleteBuffers(1, &EBO);
}

void Line::setupLine() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);
    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}
