//
//  triangles.cpp
//  OpenGL Practice
//
//  Created by Thomas Buffard on 6/27/20.
//

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);


// variables
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;


// shaders
const char* vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

const char *fragmentShaderYellowSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.9f, 0.0f, 1.0f);\n"
    "}\n\0";

const char *fragmentShaderOrangeSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.4f, 0.2f, 1.0f);\n"
    "}\n\0";


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
    
    
    // Vertex shader
    // Initialize shader object
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    // Attach shader source code to object
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    // Compile shader
    glCompileShader(vertexShader);
    
    // Check that shader compilation was successful
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        // Output error message
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    
    
    // Fragment shader orange
    // Initialize shader object
    unsigned int fragmentShaderOrange;
    fragmentShaderOrange = glCreateShader(GL_FRAGMENT_SHADER);
    // Attach shader source code to object
    glShaderSource(fragmentShaderOrange, 1, &fragmentShaderOrangeSource, NULL);
    // Compile shader
    glCompileShader(fragmentShaderOrange);
    
    // Check that shader compilation was successful
    glGetShaderiv(fragmentShaderOrange, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        // Output error message
        glGetShaderInfoLog(fragmentShaderOrange, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    
    // Fragment shader yellow
    // Initialize shader object
    unsigned int fragmentShaderYellow;
    fragmentShaderYellow = glCreateShader(GL_FRAGMENT_SHADER);
    // Attach shader source code to object
    glShaderSource(fragmentShaderYellow, 1, &fragmentShaderYellowSource, NULL);
    // Compile shader
    glCompileShader(fragmentShaderYellow);
    
    // Check that shader compilation was successful
    glGetShaderiv(fragmentShaderYellow, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        // Output error message
        glGetShaderInfoLog(fragmentShaderYellow, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    
    // Linking shaders
    // Create shader program
    // Orange shader
    unsigned int shaderProgramOrange;
    shaderProgramOrange = glCreateProgram();
    // Attach and link shaders to program
    glAttachShader(shaderProgramOrange, vertexShader);
    glAttachShader(shaderProgramOrange, fragmentShaderOrange);
    glLinkProgram(shaderProgramOrange);
    
    // Check if shader linking was successful
    glGetProgramiv(shaderProgramOrange, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetProgramInfoLog(shaderProgramOrange, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER_PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    
    // Yellow shader
    unsigned int shaderProgramYellow;
    shaderProgramYellow = glCreateProgram();
    // Attach and link shaders to program
    glAttachShader(shaderProgramYellow, vertexShader);
    glAttachShader(shaderProgramYellow, fragmentShaderYellow);
    glLinkProgram(shaderProgramYellow);
    
    // Check if shader linking was successful
    glGetProgramiv(shaderProgramYellow, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetProgramInfoLog(shaderProgramYellow, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER_PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    
    // Delete shader objects
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShaderOrange);
    glDeleteShader(fragmentShaderYellow);
    
    
    // Rectangle
    // Triangle 1
    float firstTri[] = {
         -0.5f, 0.5f, 0.0f,
         -0.5f, 0.0f, 0.0f,
         -0.1f, 0.0f, 0.0f
    };
    
    // Triangle 2
    float secondTri[] = {
        0.1f, 0.0f, 0.0f,
        0.5f, 0.5f, 0.0f,
        0.5f, 0.0f, 0.0f
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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // Second triangle
    glBindVertexArray(VAO[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(secondTri), secondTri, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
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
        
        // Render triangle
        // Activate program
        // First triangle orange
        glUseProgram(shaderProgramOrange);
        glBindVertexArray(VAO[0]);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        // Second triangle yellow
        glUseProgram(shaderProgramYellow);
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
