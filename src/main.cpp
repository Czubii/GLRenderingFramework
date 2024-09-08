#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <VAO.h>
#include <VBO.h>
#include <EBO.h>
#include <shaderClass.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include "camera.h"
#include "objectTransform.h"
#include "cameraOperator.h"
#include "mesh.h"
#include "cube.h"
#include <gtx/quaternion.hpp>
#include "obj_load.h"

static GLuint windowWidth = 820;
static GLuint windowHeight = 640;

static std::vector<Camera> cameras;

/// @brief called when window size changes, updates viewport and cameras
void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
	std::cout << "Window resized: " << width << "x" << height << std::endl;

	windowWidth = width;
	windowHeight = height;

	// update the viewport to match the new window dimensions
	glViewport(0, 0, windowWidth, windowHeight);
	for (auto &camera: cameras)
		camera.setDimensions(windowWidth, windowHeight);
}

int main() {
	// Initialize GLFW
	glfwInit();
	glfwWindowHint(GLFW_SAMPLES, 4); // Set 4x multisampling (you can adjust the value to your needs)

	// Tell GLFW what version of OpenGL we are using
	// In this case we are using OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Tell GLFW we are using the CORE profile
	// So that means we only have the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a GLFWwindow object of 800 by 800 pixels, naming it "YoutubeOpenGL"
	GLFWwindow *window = glfwCreateWindow(windowWidth, windowHeight, "YoutubeOpenGL", NULL, NULL);
	// Error check if the window fails to create
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// Introduce the window into the current context
	glfwMakeContextCurrent(window);

	// Callback function for when the window has been resized
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// Load GLAD so it configures OpenGL
	gladLoadGL();
	glEnable(GL_MULTISAMPLE);

	// Specify the viewport of OpenGL in the Window
	// In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
	glViewport(0, 0, windowWidth, windowHeight);


	std::vector<Vertex> cubeVertices(cube::vertices, cube::vertices + sizeof(cube::vertices) / sizeof(Vertex));
	std::vector<GLuint> cubeIndices(cube::indices, cube::indices + sizeof(cube::indices) / sizeof(GLuint));


	Shader shaderProgram("shaders/default.vert", "shaders/default.frag");

	auto camera = Camera(windowWidth, windowHeight);
	CameraOperator camOperator(&camera);
	Mesh testMesh = meshFromFile("test.obj");

	glEnable(GL_DEPTH_TEST);
	// this is so the vertices that should be in the front are drawn on vertices that should be in the back

	float previousTime = static_cast<float>(glfwGetTime());
	float timeDelta, currentTime;

	// Main while loop
	while (!glfwWindowShouldClose(window)) {
		currentTime = static_cast<float>(glfwGetTime());
		timeDelta = currentTime - previousTime;
		previousTime = currentTime;

		camOperator.handleInputs(window, timeDelta);
		camOperator.getCamera().updateMatrix();

		// Specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// Tell OpenGL which Shader Program we want to use
		shaderProgram.Activate();

		testMesh.draw(shaderProgram, camera, DrawMode::DEFAULT);


		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}

	// Delete all the objects we've created
	shaderProgram.Delete();

	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}
