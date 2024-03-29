//
//  shader.h
//  OpenGL Practice
//
//  Created by Thomas Buffard on 6/30/20.
//

#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

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
    
private:
    // utility function for checking shader compilation/linking errors.
    void checkCompileErrors(unsigned int shader, std::string type);
};

#endif
