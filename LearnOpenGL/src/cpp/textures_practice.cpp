//
//  textures_practice.cpp
//  OpenGL Practice
//
//  Created by Thomas Buffard on 7/1/20.
//

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <stdio.h>

#include "shader.h"
#include "stb_image.h"
#include "texture.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);


// variables
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

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
    
    
    // ------------------------------------- //
    // Shader
    Shader shaderProgram("shaders/shader_2.vert", "shaders/shader_2.frag");
    
    
    
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
    Texture boxTex("textures/container.jpg");
    Texture wallTex("textures/wall.jpg");
    
    
    // ------------------------------------- //
    // Render loop
    //Activate shaders
    shaderProgram.use();
    shaderProgram.setInt("texture1", 0);
    shaderProgram.setInt("texture2", 1);
    
    
    
    // Transforms
//    glm::mat4 trans = glm::mat4(1.0f);
//    trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
//    trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));
    
    
    // Check if window has been instructed to close
    while(!glfwWindowShouldClose(window))
    {
        // Process input
        processInput(window);
        
        // Rendering commands
        // Clear color
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);   // State setting function
        glClear(GL_COLOR_BUFFER_BIT);           // State using function
        
        // Render
        // Activate and bind texture
        glActiveTexture(GL_TEXTURE0);
        glEnable(GL_TEXTURE_2D);
        boxTex.bind();
        glActiveTexture(GL_TEXTURE1);
        glEnable(GL_TEXTURE_2D);
        wallTex.bind();
        
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
void processInput(GLFWwindow* window)
{
    // Close the window when user presses escape
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

