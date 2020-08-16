//
// Created by Thomas Buffard on 7/6/20.
//

#include "camera.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// constructor with vector
Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch) :
        Front(glm::vec3(0.0f, 0.0f, 0.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM) {
    Position = position;
    WorldUp = up;
    Yaw = yaw;
    Pitch = pitch;
    update_camera_vectors();
}

// returns the view matrix calculated using Euler Angles and the LookAt Matrix
glm::mat4 Camera::get_view_matrix() {
    return glm::lookAt(Position, Position + Front, Up);
}

// processes input received from a mouse input system.
// Expects the offset value in both the x and y direction.
void Camera::process_mouse_movement(float xoffset, float yoffset, Camera_Movement movement) {
    xoffset *= MouseSensitivity;
    yoffset *= MouseSensitivity;
    if (movement == PAN) {
        Position += Right * xoffset;
        Position += Up * yoffset;
    } else if (movement == ZOOM) {
        Position += Front * yoffset;
    } else if (movement == TILT) {
        Yaw += xoffset * 10;
        Pitch += yoffset * 10;

        if (Pitch > 89.0f)
            Pitch = 89.0f;
        if (Pitch < -89.0f)
            Pitch = -89.0f;
    }

    // update Front, Right and Up Vectors using the updated Euler angles
    update_camera_vectors();
}

// calculates the front vector from the Camera's (updated) Euler Angles
void Camera::update_camera_vectors() {
    // calculate the new Front vector
    glm::vec3 front;
    front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    front.y = sin(glm::radians(Pitch));
    front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    Front = glm::normalize(front);
    // also re-calculate the Right and Up vector
    Right = glm::normalize(glm::cross(Front, WorldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    Up = glm::normalize(glm::cross(Right, Front));
}
