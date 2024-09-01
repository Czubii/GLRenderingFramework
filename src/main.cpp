#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <VAO.h>
#include <VBO.h>
#include <EBO.h>
#include <shaderClass.h>
#include <stb_image.h>
#include <texture.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include "camera.h"
#include "objectTransform.h"
#include "cameraOperator.h"
#include "mesh.h"
#include "cube.h"
#include <gtx/quaternion.hpp>

static GLuint windowWidth = 820;
static GLuint windowHeight = 640;

static std::vector<Camera> cameras;

/// @brief called when window size changes, updates viewport and cameras
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    std::cout << "Window resized: " << width << "x" << height << std::endl;

	windowWidth = width;
	windowHeight = height;

    // update the viewport to match the new window dimensions
    glViewport(0, 0, windowWidth, windowHeight);
	for(auto & camera: cameras)
		camera.setDimensions(windowWidth, windowHeight);
}

int main()
{
	// Initialize GLFW
	glfwInit();

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
	if (window == NULL)
	{
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
	// Specify the viewport of OpenGL in the Window
	// In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
	glViewport(0, 0, windowWidth, windowHeight);

	// Vertices coordinates
	std::vector<Vertex> vertices;
	float vertArr[] =
		{//     COORDINATES     /        COLORS      /   TexCoord  //
		 -2.5f, 0.0f, 0.5f, 0.83f, 0.70f, 0.44f, 0.0f, 0.0f,
		 -0.5f, 0.0f, -0.5f, 0.83f, 0.70f, 0.44f, 5.0f, 0.0f,
		 0.5f, 0.0f, -0.5f, 0.83f, 0.70f, 0.44f, 0.0f, 0.0f,
		 0.5f, 0.0f, 0.5f, 0.83f, 0.70f, 0.44f, 5.0f, 0.0f,
		 0.0f, 0.75f, 0.0f, 0.92f, 0.86f, 0.76f, 2.5f, 5.0f};

	for (int i = 0; i < 5; i++)
	{
		int idx = i * 8;
		glm::vec3 a = glm::vec3(vertArr[idx], vertArr[idx + 1], vertArr[idx + 2]);
		glm::vec3 b = glm::vec3(vertArr[idx + 3], vertArr[idx + 4], vertArr[idx + 5]);
		glm::vec2 c = glm::vec2(static_cast<GLuint>(vertArr[idx + 6]), static_cast<GLuint>(vertArr[idx + 7]));
		Vertex vert = {a, b, c};
		vertices.push_back(vert);
	}

	// Indices for vertices order
	std::vector<GLuint> indices =
		{
			0, 1, 2,
			0, 2, 3,
			0, 1, 4,
			1, 2, 4,
			2, 3, 4,
			3, 0, 4};

	// Texture brickTexture("brick.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE); 
	Texture brickTexture(255, 255, 255, 25);

	Mesh piramid(vertices, indices, std::vector<Texture>{brickTexture});

	std::vector<Vertex> cubeVertices(cube::vertices, cube::vertices + sizeof(cube::vertices) / sizeof(Vertex));
	std::vector<GLuint> cubeIndices(cube::indices, cube::indices + sizeof(cube::indices) / sizeof(GLuint));

	Mesh cube(cubeVertices, cubeIndices, std::vector<Texture>{brickTexture});
	Mesh cube2(cubeVertices, cubeIndices, std::vector<Texture>{brickTexture});
	Shader shaderProgram("shaders/default.vert", "shaders/default.frag");

	cameras = {
	Camera(windowWidth, windowHeight),
	Camera(windowWidth, windowHeight)};

	CameraOperator camOperator(&cameras[0]);
	int cameraIdx = 0;
	bool cameraSwitched = false;

	glEnable(GL_DEPTH_TEST); // this is so the vertices that should be in the front are drawn on vertices that should be in the back

	float previousTime = static_cast<float>(glfwGetTime());
	float timeDelta, currentTime;

	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		currentTime = static_cast<float>(glfwGetTime());
		timeDelta = currentTime - previousTime;
		previousTime = currentTime;

		if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS)
		{
			if (!cameraSwitched)
			{
				cameraSwitched = true;

				cameraIdx++;

				if (cameraIdx >= cameras.size())
					cameraIdx = 0;

				camOperator.setCamera(&cameras[cameraIdx]);
			}
		}
		else
		{
			cameraSwitched = false;
		}

		camOperator.handleInputs(window, timeDelta);
		camOperator.getCamera().updateMatrix();

		// Specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// Tell OpenGL which Shader Program we want to use
		shaderProgram.Activate();

		Transform test = Transform();
		test.pos.x = 1.0f;
		test.rot = glm::quat(glm::vec3(0.0f, 1.0f, 0.0f));
		// piramid.draw(shaderProgram, camOperator.getCamera());
		cube.draw(shaderProgram, camOperator.getCamera());
		cube2.drawWireframe(shaderProgram, camOperator.getCamera(), test);
		cameras[0].drawViewBounds(shaderProgram, camOperator.getCamera());

		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}

	// Delete all the objects we've created
	brickTexture.Delete();
	shaderProgram.Delete();

	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}
