// COMP371 - Project
// main.cpp
// Created by Thomas Buffard on 6/26/20.

#define _USE_MATH_DEFINES

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Utilities/shader_m.h"
#include "Utilities/camera.h"
#include "Utilities/model.h"
#include "Utilities/texture.h"

#include "Line/line.h"

#include <iostream>
#include <istream>
#include <vector>
#include <math.h>

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void mouse_callback(GLFWwindow *window, double xpos, double ypos);
void process_input(GLFWwindow *window);
void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);

void createTimexModel();
void createAxes();

void resetTextures(const Shader &shader);

void renderScene(Shader &shader, Model cube, Model sphere);
void renderGrid(Shader &shader, Model cube);
void renderAlphanum(Shader &shader, Model cube, Model sphere);
void renderAxes(Shader &shader, Model cube);

// Settings
unsigned int SCR_WIDTH = 1024;
unsigned int SCR_HEIGHT = 768;
const float ULEN = 0.1f; // Unit Length

// Identity matrix
glm::mat4 id(1.0f);

// Cameras
Camera camera(glm::vec3(0.0f, ULEN, 20.0 * ULEN));

float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// Timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

// Render Type
GLenum type = GL_TRIANGLES;

// Selected Model
unsigned int selectedModel = 0;

// Texture Toggle
unsigned int textureOn = 1;

// Light toggle
unsigned int lightToggle = 1;

// Camera toggle
unsigned int cameraToggle = 0;

// Skybox toggle
unsigned int skyboxToggle = 0;

// Alphanumeric class
struct CubeComponent {
    std::vector<glm::mat4> cubeTrans; // Vector of Cube Meshes Transformations

    glm::mat4 adjust = id; // Digit Adjustment Matrix

    glm::mat4 rotation = id;    // Model Rotation Matrix
    glm::mat4 scale = id;       // Model Scale Matrix
    glm::mat4 translation = id; // Model Translation Matrix

    unsigned int diffuse = 0;
};

struct ModelStruct {
	std::vector<CubeComponent> components;

	glm::mat4 rotation = id;    // Model Rotation Matrix
	glm::mat4 scale = id;       // Model Scale Matrix
	glm::mat4 translation = id; // Model Translation Matrix

	float rotationAngle;
} timexModel, axesModel;

std::vector<glm::mat4> skate;

// World Orientation
glm::mat4 worldOrientation(1.0f);

// Sphere Scaling
glm::mat4 sphereScale = glm::scale(id, glm::vec3(5.0f, 5.0f, 5.0f));

// Sphere Translation
glm::mat4 sphereTranslation = glm::translate(id, glm::vec3(0.0f, 6.0 * ULEN, 0.0f));

glm::mat4 projection(1.0f);
glm::mat4 view(1.0f);

// Light position
glm::vec3 lightPos;

int main() {
    // GLFW: Initialize and configure
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // GLFW Window Creation
    GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "COMP371 Project", nullptr, nullptr);
    if (window == nullptr) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetKeyCallback(window, key_callback);

    // Tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, false);

    // Load all OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Configure Global Opengl State
    glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

    // Build and Compile our Shader Programs
    Shader sceneShader("../res/shaders/scene.vert", "../res/shaders/scene.frag");
    Shader shadowShader("../res/shaders/shadow.vert", "../res/shaders/shadow.frag");

    // Cube model
    Model cube("../res/models/cube/cube.obj");
    // Sphere model
    Model sphere("../res/models/sphere/sphere.obj");

    // Initialize alphanumeric models
	createTimexModel();
	createAxes();

    // Textures
    Texture boxTexture("res/textures/box.jpg");
    Texture groundTexture("res/textures/ground.jpg");
    Texture shinyTexture("res/textures/yellow.png");
    Texture greyTexture("res/textures/grey.png");
    Texture skybox("res/textures/skybox.jpg");

	// bind textures
	glActiveTexture(GL_TEXTURE0);
	glEnable(GL_TEXTURE_2D);
	boxTexture.bind();

	glActiveTexture(GL_TEXTURE1);
	glEnable(GL_TEXTURE_2D);
	groundTexture.bind();

	glActiveTexture(GL_TEXTURE2);
	glEnable(GL_TEXTURE_2D);
	shinyTexture.bind();

	glActiveTexture(GL_TEXTURE3);
	glEnable(GL_TEXTURE_2D);
	greyTexture.bind();


	// Depth map frame buffer
	unsigned int depthMapFBO;
	glGenFramebuffers(1, &depthMapFBO);

	// Create texture for the depth map
	const unsigned int SHADOW_WIDTH = 2048, SHADOW_HEIGHT = 2048;

	unsigned int depthMap;
	glGenTextures(1, &depthMap);
	glBindTexture(GL_TEXTURE_2D, depthMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT,
			SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Attach depth map to the frame buffer
	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);

	// Set color buffer to none
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	// Check that framebuffer is complete
	if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glActiveTexture(GL_TEXTURE4);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, depthMap);


    // Render Loop
    while (!glfwWindowShouldClose(window)) {
        // Per Frame Time Logic
        auto currentFrame = float(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Input
        process_input(window);

        glClearColor(0.0f, 0.0784f, 0.1607f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Set projection matrix
        projection = glm::perspective(45.0f, (float) SCR_WIDTH / (float) SCR_HEIGHT, 0.1f,100.0f);

        // Project camera
        if (cameraToggle == 0) {
			glm::mat4 pos = glm::translate(id, camera.Position);
			view = glm::inverse(pos) * worldOrientation * pos * camera.get_view_matrix();
        }
        // Front camera
		if (cameraToggle == 1){
			glm::mat4 pos = glm::translate(id, glm::vec3(0.0f, 5.0 * ULEN, 20.0 * ULEN));
			view =  glm::inverse(pos * timexModel.translation * glm::inverse(pos) * timexModel.rotation * pos *
					camera.get_view_matrix());
		}
		// Back camera
		if (cameraToggle == 2){
			glm::mat4 pos = glm::translate(id, glm::vec3(0.0f, 5.0 * ULEN, -20.0 * ULEN));
			view =  glm::rotate(id, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f)) *
					glm::inverse(pos * timexModel.translation * glm::inverse(pos) * timexModel.rotation * pos *
					camera.get_view_matrix());
		}
		// Light camera
		if (cameraToggle == 3){
			view = camera.get_view_matrix();
		}

		glm::mat4 lightSpaceMatrix;

        if (lightToggle) {
			// Set orthographic frustum for shadows
			float near_plane = .1f, far_plane = 10.0f;
			glm::mat4 lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);

			// View matrix from light perspective
			// Shadows only render correctly if the light is offset by some amount >0
			lightPos = glm::vec3(0.0f, 5.0 * ULEN, 30.0 * ULEN);
			glm::mat4 lightView = glm::lookAt(lightPos,
					glm::vec3( 0.0f, 3.0 * ULEN,  0.0f),
					glm::vec3( 0.0f, 1.0f,  0.0f));

			lightSpaceMatrix = lightProjection * lightView;

			shadowShader.use();
			shadowShader.setMat4("lightSpaceMatrix", lightSpaceMatrix);

			// Bind grey texture
			// Not sure why but if we don't bind it here it just renders as red
			glActiveTexture(GL_TEXTURE3);
			glEnable(GL_TEXTURE_2D);
			greyTexture.bind();

			// Set viewport size and bind depth map frame buffer
			glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
			glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			// Render scene with shadow/depth map shader
			renderScene(shadowShader, cube, sphere);

			glBindFramebuffer(GL_FRAMEBUFFER, 0);
        } else {
			// Clear frame buffer so no shadows render
			glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
			glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glBindFramebuffer(GL_FRAMEBUFFER, 0);

			lightPos = glm::vec3(0.0f);
        }

		// Reset window size
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		glViewport(0, 0, width, height);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Activate scene shader
        sceneShader.use();
        sceneShader.setMat4("projection", projection);
		sceneShader.setMat4("view", view);
		sceneShader.setMat4("world", id);
		sceneShader.setVec3("viewPos", camera.Position);
		sceneShader.setMat4("lightSpaceMatrix", lightSpaceMatrix);

		// Set shadow map
		sceneShader.setInt("shadowMap", 4);

		// Render the scene using shadow map
		renderScene(sceneShader, cube, sphere);

		// Render skybox
		resetTextures(sceneShader);
		sceneShader.setVec3("light.position", glm::vec3(0.0f));

		glActiveTexture(GL_TEXTURE5);
		glEnable(GL_TEXTURE_2D);
		skybox.bind();
		sceneShader.setInt("material.diffuse", 5);

		if(skyboxToggle) {
			sceneShader.setMat4("model", glm::scale(id, glm::vec3(75.0, 75.0, 75.0)));
			sphere.Draw(sceneShader, type);
		} else {
			glm::mat4 model = glm::translate(id, glm::vec3(0.0f, -32.5 * ULEN, 0.0f)) *
					glm::scale(id, glm::vec3(75.0, 75.0, 75.0));
			sceneShader.setMat4("model", model);
			cube.Draw(sceneShader, type);
		}

		// Reset framebuffer
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

        // GLFW: Swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
    return 0;
}

void renderScene(Shader &shader, Model cube, Model sphere)
{
	renderGrid(shader, cube);
	renderAlphanum(shader, cube, sphere);
	renderAxes(shader, cube);
}

void renderGrid(Shader &shader, Model cube)
{
	GLenum type = GL_LINES;

	if (textureOn == 1) {
		shader.setVec3("material.ambient", 0.5f, 0.5f, 0.5f);
		shader.setInt("material.diffuse", 1);
		shader.setVec3("material.specular", 0.2f, 0.2f, 0.2f);
		shader.setFloat("material.shininess", 32.0f);

		// light properties
		shader.setVec3("light.ambient", 0.2f, 0.2f, 0.2f);
		shader.setVec3("light.diffuse", 1.0f, 1.0f, 1.0f);
		shader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);
		shader.setVec3("light.position", lightPos);
		type = GL_TRIANGLES;

	} else {
		resetTextures(shader);
		shader.setInt("material.diffuse", 3);
		type = GL_LINES;
	}

	for (int i = -50; i < 50; i++) {
		for (int j = -50; j < 50; j++) {
			glm::vec3 pos((float) i * ULEN, -1.0 * ULEN, (float) j * ULEN);
			glm::mat4 model = glm::translate(id, pos);
			shader.setMat4("model", model);

			cube.Draw(shader, type);
		}
	}
}

void renderAlphanum(Shader &shader, Model cube, Model sphere)
{
	if (textureOn == 1) {
		shader.setVec3("material.ambient", 0.5f, 0.5f, 0.5f);
		shader.setVec3("material.specular", 0.2f, 0.2f, 0.2f);
		shader.setFloat("material.shininess", 32.0f);

		// light properties
		shader.setVec3("light.ambient", 0.2f, 0.2f, 0.2f);
		shader.setVec3("light.diffuse", 1.0f, 1.0f, 1.0f);
		shader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);
		shader.setVec3("light.position", lightPos);
	} else {
		resetTextures(shader);
	}

	// render each alphanumeric pair by looping through the array of models
	for (unsigned int j = 0; j < timexModel.components.size(); j++) {
		// add box texture
		if (textureOn == 1) {
			shader.setInt("material.diffuse", timexModel.components[j].diffuse);
		} else {
			shader.setInt("material.diffuse", 3);
			resetTextures(shader);
		}
		// draw the letter
		for (unsigned int i = 0; i < timexModel.components[j].cubeTrans.size(); i++) {

			glm::mat4 model =
					timexModel.translation * timexModel.rotation * timexModel.scale *
					timexModel.components[j].adjust * timexModel.components[j].translation * timexModel.components[j].rotation *
					timexModel.components[j].scale * timexModel.components[j].cubeTrans[i];
			shader.setMat4("model", model);

			cube.Draw(shader, type);
		}
	}

	// add shiny texture
	shader.setInt("material.diffuse", 3);
	shader.setInt("material.diffuse", 3);
	shader.setVec3("material.specular", 1.0f, 1.0f, 1.0f);
	shader.setFloat("material.shininess", 64.0f);

	glm::mat4 skateTrans[2] = {
			glm::translate(id, glm::vec3(-3.5*ULEN, 0.0f, 0.0f)),
			glm::translate(id, glm::vec3(3.5*ULEN, 0.0f, 0.0f))
	};

	// Render skates
	for (unsigned int j = 0; j < 2; j++) {
		for (unsigned int i = 0; i < skate.size(); i++) {
			glm::mat4 model =
					timexModel.translation * timexModel.rotation * timexModel.scale *
					skateTrans[j] * skate[i];
			shader.setMat4("model", model);

			cube.Draw(shader, type);
		}
	}
}

void renderAxes(Shader &shader, Model cube) {
	resetTextures(shader);

	for (unsigned int j = 0; j < axesModel.components.size(); j++) {
		// set texture
		shader.setInt("material.diffuse", axesModel.components[j].diffuse);
		// draw the letter
		for (unsigned int i = 0; i < axesModel.components[j].cubeTrans.size(); i++) {

			glm::mat4 model =
					axesModel.translation * axesModel.rotation * axesModel.scale *
					axesModel.components[j].adjust * axesModel.components[j].translation * axesModel.components[j].rotation *
					axesModel.components[j].scale * axesModel.components[j].cubeTrans[i];
			shader.setMat4("model", model);

			cube.Draw(shader, type);
		}
	}
}

void resetTextures(const Shader &shader) {
    shader.setVec3("material.ambient", 0.3f, 0.3f, 0.3f);
    shader.setVec3("material.specular", 0.2f, 0.2f, 0.2f);
    shader.setFloat("material.shininess", 32.0f);

    // light properties
    shader.setVec3("light.ambient", 0.2f, 0.2f, 0.2f);
    shader.setVec3("light.diffuse", 1.0f, 1.0f, 1.0f);
    shader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);
    shader.setVec3("light.position", lightPos);
}

// Process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
void process_input(GLFWwindow *window) {}

// GLFW: Whenever the window size changed (by OS or user resize), this callback function executes
void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
    SCR_WIDTH = width;
    SCR_HEIGHT = height;
}

// GLFW: Whenever the mouse moves, this callback is called
void mouse_callback(GLFWwindow *window, double xpos, double ypos) {
	if (cameraToggle == 0) {
		if (firstMouse) {
			lastX = float(xpos);
			lastY = float(ypos);
			firstMouse = false;
		}

		auto xoffset = float(xpos - lastX);
		auto yoffset = float(lastY - ypos); // Reversed since y-coordinates go from bottom to top

		lastX = float(xpos);
		lastY = float(ypos);

		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
			camera.process_mouse_movement(xoffset, 0, PAN);
		} else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
			camera.process_mouse_movement(0, yoffset, ZOOM);
		} else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS) {
			camera.process_mouse_movement(0, yoffset, TILT);
		}
	}
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {

    //Close window by pressing Escape
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }

    // L to toggle lighting
	if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {
		if (lightToggle) { lightToggle = 0; } else { lightToggle = 1; }
	}

	// Q to toggle skybox
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
		if (skyboxToggle) { skyboxToggle = 0; } else { skyboxToggle = 1; }
	}

	// Camera views
	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
		cameraToggle = 0;
		camera = Camera(glm::vec3(0.0f, ULEN, 20.0 * ULEN));
		worldOrientation = glm::mat4(1.0f);
	}
	if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS) {
		cameraToggle = 1;
		camera = Camera(glm::vec3(0.0f));
	}
	if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS) {
		cameraToggle = 2;
		camera = Camera(glm::vec3(0.0f, ULEN, 20.0 * ULEN));
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		cameraToggle = 3;
		camera = Camera(lightPos - glm::vec3(0.0f, 0.0f, 1.0 *ULEN));
	}

    // Press U to scale up model
    if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS) {
        timexModel.scale = glm::scale(timexModel.scale,
                                                 glm::vec3(1.0f + ULEN, 1.0f + ULEN, 1.0f + ULEN));
    }
    // Press J to scale down model
    if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) {
		timexModel.scale = glm::scale(timexModel.scale,
                                                 glm::vec3(1.0f - ULEN, 1.0f - ULEN, 1.0f - ULEN));
    }
    // Press Shift + W to translate model in the -Z direction
    if ((glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        && ((glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
            || (glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS))) {
        timexModel.translation = glm::translate(timexModel.translation,
                                                           glm::vec3(0.0f, 0.0f, -ULEN));
    }

    // Press Shift + A to translate model in the -X direction
    // Press A to rotate model by -5.0 degrees
    if ((glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        && ((glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
            || (glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS))) {
        timexModel.translation = glm::translate(timexModel.translation,
                                                           glm::vec3(-ULEN, 0.0f, 0.0f));
    } else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        timexModel.rotationAngle = timexModel.rotationAngle - 5.0f;
        timexModel.rotation = glm::rotate(timexModel.rotation,
                                                     glm::radians(-5.0f),
                                                     glm::vec3(0.0f, 1.0f, 0.0f));

    }

    // Press Shift + S to translate model in the Z direction
    if ((glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        && ((glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
            || (glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS))) {
        timexModel.translation = glm::translate(timexModel.translation,
                                                           glm::vec3(0.0f, 0.0f, ULEN));
    }

    // Press Shift + D to translate model in the X direction
    // Press D to rotate selected model by 5.0 degrees
    if ((glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        && ((glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
            || (glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS))) {
        timexModel.translation = glm::translate(timexModel.translation,
                                                           glm::vec3(ULEN, 0.0f, 0.0f));
    } else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        timexModel.rotationAngle = timexModel.rotationAngle + 5.0f;
        timexModel.rotation = glm::rotate(timexModel.rotation,
                                                     glm::radians(5.0f),
                                                     glm::vec3(0.0f, 1.0f, 0.0f));
    }

    // Press Left Arrow Key to Rx
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        worldOrientation = glm::rotate(worldOrientation, glm::radians(5.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    }

    // Press Right Arrow Key to R-x
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        worldOrientation = glm::rotate(worldOrientation, glm::radians(-5.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    }

    // Reset world orientation and camera by pressing Home button
    if (glfwGetKey(window, GLFW_KEY_HOME) == GLFW_PRESS) {
        worldOrientation = glm::mat4(1.0f);
        camera = Camera(glm::vec3(0.0f, 0.1f, 2.0f));
		createTimexModel();
    }
}

void createTimexModel() {
	// Letter T
	CubeComponent T;
	T.cubeTrans.push_back(
			glm::scale(id, glm::vec3(1.0f, 4.0f, 1.0f))
			);
	T.cubeTrans.push_back(
			glm::translate(id, glm::vec3(0.0*ULEN, 4.0*ULEN, 0.0*ULEN)) *
			glm::scale(id, glm::vec3(3.0f, 1.0f, 1.0f))
	);
	T.adjust = glm::translate(id, glm::vec3(-6.0*ULEN, 2.0*ULEN, 0.0*ULEN));
	T.diffuse = 0;
	timexModel.components.push_back(T);

	// Number 3
	CubeComponent three;
	three.cubeTrans.push_back(
			glm::translate(id, glm::vec3(1.5*ULEN, 0.0*ULEN, 0.0*ULEN)) *
			glm::scale(id, glm::vec3(1.0f, 5.0f, 1.0f)));
	three.cubeTrans.push_back(
			glm::translate(id, glm::vec3(0.0*ULEN, 0.0*ULEN, 0.0*ULEN)) *
			glm::scale(id, glm::vec3(2.0f, 1.0f, 1.0f)));
	three.cubeTrans.push_back(
			glm::translate(id, glm::vec3(0.0*ULEN, 2.0*ULEN, 0.0*ULEN)) *
			glm::scale(id, glm::vec3(2.0f, 1.0f, 1.0f)));
	three.cubeTrans.push_back(
			glm::translate(id, glm::vec3(0.0*ULEN, 4.0*ULEN, 0.0*ULEN)) *
			glm::scale(id, glm::vec3(2.0f, 1.0f, 1.0f)));
	three.adjust = glm::translate(id, glm::vec3(-2.5*ULEN, 2.0*ULEN, 0.0*ULEN));
	three.diffuse = 1;
	timexModel.components.push_back(three);

	// Letter H
	CubeComponent H;
	H.cubeTrans.push_back(
			glm::translate(id, glm::vec3(-1.0 * ULEN, 0.0f, 0.0f)) *
			glm::scale(id, glm::vec3(1.0f, 5.0f, 1.0f)));
	H.cubeTrans.push_back(
			glm::translate(id, glm::vec3(0.0f, 2.0 * ULEN, 0.0f)));
	H.cubeTrans.push_back(
			glm::translate(id, glm::vec3(1.0 * ULEN, 0.0f, 0.0f)) *
			glm::scale(id, glm::vec3(1.0f, 5.0f, 1.0f)));
	H.adjust = glm::translate(id, glm::vec3(2.0*ULEN, 2.0*ULEN, 0.0*ULEN));
	H.diffuse = 2;
	timexModel.components.push_back(H);

	// Number 2
	CubeComponent two;
	two.cubeTrans.push_back(
			glm::scale(id, glm::vec3(3.0f, 1.0f, 1.0f)));
	two.cubeTrans.push_back(
			glm::translate(id, glm::vec3(0.0 * ULEN, 4.0 * ULEN, 0.0 * ULEN)) *
			glm::scale(id, glm::vec3(3.0f, 1.0f, 1.0f)));
	two.cubeTrans.push_back(
			glm::translate(id, glm::vec3(0.0 * ULEN, 2.0 * ULEN, 0.0 * ULEN)) *
			glm::scale(id, glm::vec3(3.0f, 1.0f, 1.0f)));
	two.cubeTrans.push_back(
			glm::translate(id, glm::vec3(-1.0 * ULEN, 1.0 * ULEN, 0.0 * ULEN)));
	two.cubeTrans.push_back(
			glm::translate(id, glm::vec3(1.0 * ULEN, 3.0 * ULEN, 0.0 * ULEN)));
	two.adjust = glm::translate(id, glm::vec3(6.0*ULEN, 2.0*ULEN, 0.0*ULEN));
	two.diffuse = 3;
	timexModel.components.push_back(two);

	// Skate model
	skate.push_back(
			glm::translate(id, glm::vec3(0.0 * ULEN, 1.0 * ULEN, 0.0 * ULEN)) *
			glm::scale(id, glm::vec3(3.0f, 1.0f, 4.0f)));
	skate.push_back(
			glm::scale(id, glm::vec3(1.0f, 1.0f, 4.0f)));
}

void createAxes() {
	glm::mat4 shearLeft = {
			1.0f, 0.0f, 0.0f, 0.0f,
			-1.0, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
	};
	glm::mat4 shearRight = {
			1.0f, 0.0f, 0.0f, 0.0f,
			1.0, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
	};

	std::vector<glm::mat4> arrow;
	arrow.push_back(
			glm::scale(id, glm::vec3(0.25f, 5.0f, 0.25f)));
	arrow.push_back(
			glm::translate(id, glm::vec3(-0.25*ULEN, 4.5*ULEN, 0.*ULEN)) *
			glm::scale(id, glm::vec3(0.25f, 0.5f, 0.25f)) * shearRight);
	arrow.push_back(
			glm::translate(id, glm::vec3(0.25*ULEN, 4.5*ULEN, 0.*ULEN)) *
			glm::scale(id, glm::vec3(0.25f, 0.5f, 0.25f)) * shearLeft);

	CubeComponent X;
	X.cubeTrans = arrow;
	X.rotation = glm::rotate(id, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	X.rotation = glm::rotate(X.rotation, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	X.diffuse = 3;

	CubeComponent Y;
	Y.cubeTrans = arrow;
	Y.diffuse = 3;

	CubeComponent Z;
	Z.cubeTrans = arrow;
	Z.rotation = glm::rotate(id, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	Z.rotation = glm::rotate(X.rotation, glm::radians(-90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	Z.diffuse = 3;

	axesModel.components.push_back(X);
	axesModel.components.push_back(Y);
	axesModel.components.push_back(Z);
}

