#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

// Abstract shader class that generates a shader program from
// a specified vertex shader and fragment shader
class Shader
{
public:
    unsigned int ID;
    // Constructor generates the shader on the fly
    Shader(const char* vertexPath, const char* fragmentPath);

    // Activate the shader
    void use() const;

    // utility uniform functions
    // Bool uniform function
    void setBool(const std::string &name, bool value) const;
    // Int uniform function
    void setInt(const std::string &name, int value) const;
    // Float uniform function
    void setFloat(const std::string &name, float value) const;
    // Vec2 uniform function
    void setVec2(const std::string &name, const glm::vec2 &value) const;
    void setVec2(const std::string &name, float x, float y) const;
    // Vec3 uniform function
    void setVec3(const std::string &name, const glm::vec3 &value) const;
    void setVec3(const std::string &name, float x, float y, float z) const;
    // Vec4 uniform function
    void setVec4(const std::string &name, const glm::vec4 &value) const;
    void setVec4(const std::string &name, float x, float y, float z, float w) const;
    // Mat2 uniform function
    void setMat2(const std::string &name, const glm::mat2 &mat) const;
    // Mat3 uniform function
    void setMat3(const std::string &name, const glm::mat3 &mat) const;
    // Mat4 uniform function
    void setMat4(const std::string &name, const glm::mat4 &mat) const;

private:
    // Utility function for checking shader compilation/linking errors.
    void checkCompileErrors(GLuint shader, std::string type);
};
#endif