#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
enum Camera_Movement {
    TILT,
    PAN,
    ZOOM
};

// Default camera values
 const float YAW = -90.0f;
 const float PITCH = 0.0f;
 const float SPEED = 2.5f;
 const float SENSITIVITY = 0.005f;

// An abstract camera class that processes input and calculates the
// corresponding Euler Angles, Vectors and Matrices for use in OpenGL
class Camera
{
public:
    // camera Attributes
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;

    // euler Angles
    float Yaw;
    float Pitch;

    // camera options
    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;

    // constructor with vector
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
           glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
           float yaw = YAW,
           float pitch = PITCH);

    // returns the view matrix calculated using Euler Angles and the LookAt Matrix
    glm::mat4 get_view_matrix();

    // processes input received from a mouse input system.
    // Expects the offset value in both the x and y direction.
    void process_mouse_movement(float xoffset, float yoffset, Camera_Movement movement);

private:
    // calculates the front vector from the Camera's (updated) Euler Angles
    void update_camera_vectors();
};

#endif