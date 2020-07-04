//
// Created by Thomas Buffard on 7/4/20.
//

#ifndef COMP371_CAMERA_H
#define COMP371_CAMERA_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/ext.hpp>
#include "hpp/shader.h"

class Camera {
public:
    Camera(Shader shaderProgram);

    void move(glm::vec3 direction, glm::vec2 rotation, float frametime);
private:
    glm::mat4 view_;
    glm::vec3 camera_pos_;
    glm::quat camera_orientation_;
    const float camera_speed_;
    Shader shader;
};


#endif //COMP371_CAMERA_H
