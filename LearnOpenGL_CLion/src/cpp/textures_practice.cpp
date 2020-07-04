//
//  textures_practice.cpp
//  OpenGL Practice
//
//  Created by Thomas Buffard on 7/1/20.
//

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/ext.hpp>

#include <stdio.h>

#include "hpp/shader.h"
#include "stb/stb_image.h"
#include "hpp/texture.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window, Shader shaderProgram);


// variables
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
glm::mat4 movementMatrix = glm::mat4(1.0f);

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
    //glEnable(GL_CULL_FACE);

    // ------------------------------------- //
    // Variables
    const float rotationSpeed = 5.0f;
    float lastFrameTime = glfwGetTime();
    float angle = 45.0f;



    // ------------------------------------- //
    // Shader
    Shader shaderProgram("src/shaders/shader_2.vert", "src/shaders/shader_2.frag");
    
    
    
    // ------------------------------------- //
    // Vertex inputs
    // Rectangle
    float vertices[] = {
        // positions          // colors           // texture coords
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left
    };
    unsigned int indices[] = {
        0, 1, 3,    // first triangle
        1, 2, 3     // second triangle
    };
    
    
    // ------------------------------------- //
    // Initialize Vertex Buffer Object, Vertex Array Object,
    // and Element Array Buffer
    unsigned int VBO, VAO, EBO;
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glGenVertexArrays(1, &VAO);
    // Bind VAO
    glBindVertexArray(VAO);
    // Bind VBO and copy vertices into vertex buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // Bind EBO and copy indices into element buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
    
    
    // Wireframe
//    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    
    
    
    // ------------------------------------- //
    // Textures
    Texture boxTex("assets/textures/container.jpg");
    Texture wallTex("assets/textures/wall.jpg");
    
    
    // ------------------------------------- //
    // Render loop
    //Activate shaders
    shaderProgram.use();
    shaderProgram.setInt("texture1", 0);
    shaderProgram.setInt("texture2", 1);
    
    // Check if window has been instructed to close
    while(!glfwWindowShouldClose(window))
    {
        // Process input
        processInput(window, shaderProgram);
        
        // Rendering commands
        // Clear color
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);   // State setting function
        glClear(GL_COLOR_BUFFER_BIT);           // State using function
        
        // Render
        shaderProgram.use();
        // Activate and bind texture
        glActiveTexture(GL_TEXTURE0);
        glEnable(GL_TEXTURE_2D);
        boxTex.bind();
        glActiveTexture(GL_TEXTURE1);
        glEnable(GL_TEXTURE_2D);
        wallTex.bind();
        
        // Calculate world matrix
        float dt = glfwGetTime() - lastFrameTime;
        lastFrameTime += dt;
        
        angle = (angle + rotationSpeed * dt);
        //angle = 45.0f;
        //glm::mat4 trans = glm::mat4(1.0f);
        glm::mat4 trans = glm::translate(glm::mat4(1.0f), glm::vec3(0.5f, -0.5f, 0.0f));
        glm::mat4 rotationMatrix = glm::rotate(trans, glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f));
        GLuint worldMatrixLocation = glGetUniformLocation(shaderProgram.ID, "worldMatrix");
        glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &rotationMatrix[0][0]);
        
        // Draw rectangle
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // top right rectangle
        trans = glm::translate(glm::mat4(1.0f), glm::vec3(-0.5f, 0.5f, 0.0f));
        glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(0.25f, -0.25f, 0.25f));
        glm::mat4 worldMatrix = trans * scaleMatrix;
        glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &worldMatrix[0][0]);

        // Draw rectangle
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


        // Check for event triggers and swap buffers
        glfwPollEvents();
        glfwSwapBuffers(window);
    }
    
    // De-allocate resources
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    
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
void processInput(GLFWwindow* window, Shader shaderProgram)
{
    // Close the window when user presses escape
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    // Camera 1 centered at the origin
    if(glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
    {
        glm::mat4 viewMatrix = glm::mat4(1.0f);
        GLuint viewMatrixLocation = glGetUniformLocation(shaderProgram.ID, "viewMatrix");
        glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &viewMatrix[0][0]);
    }

    // Camera 2 to the left
    if(glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
    {
        glm::mat4 viewMatrix = glm::lookAt(glm::vec3(-0.5f, 0.0f, 0.0f),
                                           glm::vec3(-0.5f, 0.0f,-1.0f),
                                           glm::vec3( 0.0f, 1.0f, 0.0f) );
        GLuint viewMatrixLocation = glGetUniformLocation(shaderProgram.ID, "viewMatrix");
        glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &viewMatrix[0][0]);
    }

    // Camera 3 perspective
    if(glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
    {
        glm::mat4 projectionMatrix = glm::perspective(70.0f, 800.0f / 600.0f, 0.01f, 100.0f);
        GLuint projectionMatrixLocation = glGetUniformLocation(shaderProgram.ID, "projectionMatrix");
        glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, &projectionMatrix[0][0]);
    }

    // Camera 4 orthographic
    if(glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
    {
        glm::mat4 projectionMatrix = glm::ortho(-4.0f, 4.0f, -3.0f, 3.0f, -100.0f, 100.0f);
        GLuint projectionMatrixLocation = glGetUniformLocation(shaderProgram.ID, "projectionMatrix");
        glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, &projectionMatrix[0][0]);
    }

    // Camera movement controls
    // A: move left
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        movementMatrix = glm::translate(movementMatrix, glm::vec3(0.005f, 0.0f, 0.0f));
        GLuint  movementMatrixLocation = glGetUniformLocation(shaderProgram.ID, "movementMatrix");
        glUniformMatrix4fv(movementMatrixLocation, 1, GL_FALSE, &movementMatrix[0][0]);
    }
    // S: move up
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        movementMatrix = glm::translate(movementMatrix, glm::vec3(0.0f, 0.005f, 0.0f));
        GLuint  movementMatrixLocation = glGetUniformLocation(shaderProgram.ID, "movementMatrix");
        glUniformMatrix4fv(movementMatrixLocation, 1, GL_FALSE, &movementMatrix[0][0]);
    }
    // D: move right
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        movementMatrix = glm::translate(movementMatrix, glm::vec3(-0.005f, 0.0f, 0.0f));
        GLuint  movementMatrixLocation = glGetUniformLocation(shaderProgram.ID, "movementMatrix");
        glUniformMatrix4fv(movementMatrixLocation, 1, GL_FALSE, &movementMatrix[0][0]);
    }
    // W: move down
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        movementMatrix = glm::translate(movementMatrix, glm::vec3(0.0f, -0.005f, 0.0f));
        GLuint  movementMatrixLocation = glGetUniformLocation(shaderProgram.ID, "movementMatrix");
        glUniformMatrix4fv(movementMatrixLocation, 1, GL_FALSE, &movementMatrix[0][0]);
    }
}

