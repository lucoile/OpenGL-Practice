//
//  shader.h
//  OpenGL Practice
//
//  Created by Thomas Buffard on 6/30/20.
//

#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <glm/ext.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:
    // program id
    unsigned int ID;
    
    // constructor that reads and builds the shader
    Shader(const char* vertexPath, const char* fragmentPath);
    
    // activate shader
    void use();
    
    // utility uniform functions
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
    void setMat4(const std::string &name, glm::mat4 &matrix) const;

    void setVec3(const std::string &name, const glm::vec3 &value) const;

private:
    // utility function for checking shader compilation/linking errors.
    void checkCompileErrors(unsigned int shader, std::string type);
};

#endif
