//
// Created by Thomas Buffard on 7/13/20.
//

//
//  textures_practice.cpp
//  OpenGL Practice
//
//  Created by Thomas Buffard on 7/1/20.
//

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/ext.hpp>

#include <iostream>

#include "hpp/shader.h"
#include "stb/stb_image.h"
#include "hpp/texture.h"
#include "hpp/camera.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window, Shader shaderProgram, Camera camera, float frametime);


// variables
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
glm::mat4 movementMatrix = glm::mat4(1.0f);
glm::vec2 rotation = glm::vec2(0.0f);;
glm::vec3 direction = glm::vec3(0.0f);



int main(int argc, const char * argv[]) {
    // Initialize GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // Create GLFW window object
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Register framebuffer_size_callback function with window resizing
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Make sure GLAD is initialized
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Enable backface culling
    glEnable(GL_CULL_FACE);

//    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);

    // ------------------------------------- //
    // Variables
    const float rotationSpeed = 5.0f;
    float angle = 45.0f;
    float lastFrameTime = glfwGetTime();



    // ------------------------------------- //
    // Shader
    Shader shaderProgram("src/shaders/cube.vert", "src/shaders/cube.frag");


    // ------------------------------------- //
    // Camera
    Camera camera;

    // ------------------------------------- //
    // Calculate MVP
    glm::mat4 Projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
    // Camera matrix
    glm::mat4 View = glm::lookAt(
            glm::vec3(4,3,-3), // Camera is at (4,3,-3), in World Space
            glm::vec3(0,0,0), // and looks at the origin
            glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
    );
    // Model matrix : an identity matrix (model will be at the origin)
    glm::mat4 Model = glm::mat4(1.0f);
    // Our ModelViewProjection : multiplication of our 3 matrices
    glm::mat4 MVP = Projection * View * Model; // Remember, matrix multiplication is the other way around


    // ------------------------------------- //
    // Vertex inputs
    // Rectangle

    // Cube
    static const GLfloat vertex_data[] = {
            -1.0f,-1.0f,-1.0f, // triangle 1 : begin
            -1.0f,-1.0f, 1.0f,
            -1.0f, 1.0f, 1.0f, // triangle 1 : end
            1.0f, 1.0f,-1.0f, // triangle 2 : begin
            -1.0f,-1.0f,-1.0f,
            -1.0f, 1.0f,-1.0f, // triangle 2 : end
            1.0f,-1.0f, 1.0f,
            -1.0f,-1.0f,-1.0f,
            1.0f,-1.0f,-1.0f,
            1.0f, 1.0f,-1.0f,
            1.0f,-1.0f,-1.0f,
            -1.0f,-1.0f,-1.0f,
            -1.0f,-1.0f,-1.0f,
            -1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f,-1.0f,
            1.0f,-1.0f, 1.0f,
            -1.0f,-1.0f, 1.0f,
            -1.0f,-1.0f,-1.0f,
            -1.0f, 1.0f, 1.0f,
            -1.0f,-1.0f, 1.0f,
            1.0f,-1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f,-1.0f,-1.0f,
            1.0f, 1.0f,-1.0f,
            1.0f,-1.0f,-1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f,-1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f, 1.0f,-1.0f,
            -1.0f, 1.0f,-1.0f,
            1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f,-1.0f,
            -1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f, 1.0f,
            1.0f,-1.0f, 1.0f
    };

    static const GLfloat color_data[] = {
            0.583f,  0.771f,  0.014f,
            0.609f,  0.115f,  0.436f,
            0.327f,  0.483f,  0.844f,
            0.822f,  0.569f,  0.201f,
            0.435f,  0.602f,  0.223f,
            0.310f,  0.747f,  0.185f,
            0.597f,  0.770f,  0.761f,
            0.559f,  0.436f,  0.730f,
            0.359f,  0.583f,  0.152f,
            0.483f,  0.596f,  0.789f,
            0.559f,  0.861f,  0.639f,
            0.195f,  0.548f,  0.859f,
            0.014f,  0.184f,  0.576f,
            0.771f,  0.328f,  0.970f,
            0.406f,  0.615f,  0.116f,
            0.676f,  0.977f,  0.133f,
            0.971f,  0.572f,  0.833f,
            0.140f,  0.616f,  0.489f,
            0.997f,  0.513f,  0.064f,
            0.945f,  0.719f,  0.592f,
            0.543f,  0.021f,  0.978f,
            0.279f,  0.317f,  0.505f,
            0.167f,  0.620f,  0.077f,
            0.347f,  0.857f,  0.137f,
            0.055f,  0.953f,  0.042f,
            0.714f,  0.505f,  0.345f,
            0.783f,  0.290f,  0.734f,
            0.722f,  0.645f,  0.174f,
            0.302f,  0.455f,  0.848f,
            0.225f,  0.587f,  0.040f,
            0.517f,  0.713f,  0.338f,
            0.053f,  0.959f,  0.120f,
            0.393f,  0.621f,  0.362f,
            0.673f,  0.211f,  0.457f,
            0.820f,  0.883f,  0.371f,
            0.982f,  0.099f,  0.879f
    };


    // ------------------------------------- //
    // Initialize Vertex Buffer Object, Vertex Array Object
    unsigned int VBO, VAO;
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);
    // Bind VAO
    glBindVertexArray(VAO);
    // Bind VBO and copy vertices into vertex buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_data), vertex_data, GL_STATIC_DRAW);
    // Bind EBO and copy indices into element buffer
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // color attribute
    GLuint colorbuffer;
    glGenBuffers(1, &colorbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(color_data), color_data, GL_STATIC_DRAW);

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    // texture attribute


    // ------------------------------------- //
    // Render loop
    //Activate shaders
    shaderProgram.use();

    // Check if window has been instructed to close
    while(!glfwWindowShouldClose(window))
    {
        // Get frame time
        float dt = glfwGetTime() - lastFrameTime;
        lastFrameTime += dt;

        // Process input
        processInput(window, shaderProgram, camera, lastFrameTime);

        // Rendering commands
        // Clear color
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);   // State setting function
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);           // State using function

        // Render
        shaderProgram.use();
        shaderProgram.setMat4("MVP", MVP);

        // Draw cube
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 12*3);


        // Check for event triggers and swap buffers
        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    // De-allocate resources
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    // ------------------------------------- //
    // Clean all the GLFW resources
    glfwTerminate();
    return 0;
}


// Function called when the window is resized
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // Set the viewport window
    glViewport(0, 0, width, height);
}


// Function to process input
void processInput(GLFWwindow* window, Shader shaderProgram, Camera camera, float frametime)
{
    // Close the window when user presses escape
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

