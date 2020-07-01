//
//  shaders_practice.cpp
//  OpenGL Practice
//
//  Created by Thomas Buffard on 6/30/20.
//


#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <cmath>

#include "shader.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);


// variables
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
const float offset = 0.2f;


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
    
    Shader shaderProgram("shaders/shader_1.vertex", "shaders/shader_1.fragment");
    
    // Vertex inputs
    // Triangle 1
    float firstTri[] = {
        -0.5f, 0.5f, 0.0f,     1.0f, 0.0f, 0.0f,
        -0.5f, 0.0f, 0.0f,     0.0f, 1.0f, 0.0f,
        -0.1f, 0.0f, 0.0f,     0.0f, 0.0f, 1.0f
    };
    
    // Triangle 2
    float secondTri[] = {
        0.1f, 0.0f, 0.0f,       0.0f, 0.0f, 1.0f,
        0.5f, 0.5f, 0.0f,       0.0f, 1.0f, 0.0f,
        0.5f, 0.0f, 0.0f,       1.0f, 0.0f, 0.0f
    };
    
    // Initialize Vertex Buffer Object, Vertex Array Object,
    // and Element Array Buffer
    unsigned int VBO[2], VAO[2];
    glGenBuffers(2, VBO);
    glGenVertexArrays(2, VAO);
    
    // First triangle
    glBindVertexArray(VAO[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(firstTri), firstTri, GL_STATIC_DRAW);
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);
    
    // Second triangle
    glBindVertexArray(VAO[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(secondTri), secondTri, GL_STATIC_DRAW);
    // position atribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);
    
    // Wireframe
//    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    
    // Render loop
    // Check if window has been instructed to close
    while(!glfwWindowShouldClose(window))
    {
        // Process input
        processInput(window);
        
        // Rendering commands
        // Clear color
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);   // State setting function
        glClear(GL_COLOR_BUFFER_BIT);           // State using function
        
        // Get triangle color
//        float timeValue = glfwGetTime();
//        float greenValue = (sin(timeValue) / 2.0f) +0.5f;
        
        // Render triangle
        // Activate program
        shaderProgram.use();
        
        // set offset
        shaderProgram.setFloat("xOffset", offset);
                
        // Set color
//        shaderProgram.setFloat("ourColor", greenValue);
        
        // First triangle
        glBindVertexArray(VAO[0]);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        
        // Second triangle yellow
        glBindVertexArray(VAO[1]);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        
        glBindVertexArray(0);
        
        // Check for event triggers and swap buffers
        glfwPollEvents();
        glfwSwapBuffers(window);
    }
    
    
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

