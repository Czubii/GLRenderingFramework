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

inline float pulsatingFloat(){
	return (sin(glfwGetTime())+2) / 5;
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
	GLFWwindow *window = glfwCreateWindow(800, 800, "YoutubeOpenGL", NULL, NULL);
	// Error check if the window fails to create
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// Introduce the window into the current context
	glfwMakeContextCurrent(window);

	// Load GLAD so it configures OpenGL
	gladLoadGL();
	// Specify the viewport of OpenGL in the Window
	// In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
	glViewport(0, 0, 800, 800);

	// Vertices coordinates
	GLfloat vertices[] =
		{
			//   COORDINATES   /  	/     COLORS     / /  texture coord 	//
			-0.5f, 	-0.5f, 0.0f, 	1.0f, 0.0f, 0.0f,	   0.0f, 1.0f,	// Upper left 	corner
			0.5f, 	-0.5f, 0.0f, 	0.0f, 1.0f, 0.0f,	   1.0f, 1.0f,	// Upper right 	corner
			0.5f, 	 0.5f, 0.0f, 	1.0f, 0.0f, 1.0f,	   1.0f, 0.0f,	// Lower right 	corner
			-0.5f,   0.5f, 0.0f, 	1.0f, 1.0f, 1.0f, 	   0.0f, 0.0f 	// Lower left 	corner
		};

	// Indices for vertices order
	GLuint indices[] =
		{
			0, 1, 2, // Lower left triangle
			2, 3, 0 // Upper right triangle
		};

	Shader shaderProgram("shaders/default.vert", "shaders/default.frag");

	VAO VAO1;
	VAO1.Bind();

	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indices, sizeof(indices));

	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void *)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void *)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void *)(6 * sizeof(float)));

	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	// Retrieve the location of the "scale" uniform variable in the shader program.
	// This location is used to set or query the value of the uniform in the shader.
	GLuint UniID = glGetUniformLocation(shaderProgram._ID, "scale");

	GLfloat scale = 0.0f;


	int imgWidth, imgHeight, numColChanells;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* imgBytes = stbi_load("texture.png", &imgWidth, &imgHeight, &numColChanells, 0);

	Texture cuteCatUwU("texture.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	cuteCatUwU.texUnit(shaderProgram, "tex0", 0);


	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		scale += 0.00001f;

		// Specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT);
		// Tell OpenGL which Shader Program we want to use
		shaderProgram.Activate();
		cuteCatUwU.Bind();
		// Set the value of the "scale" uniform variable in the shader program
		// This updates the shader with the new scale factor for rendering.
		glUniform1f(UniID, pulsatingFloat());
		// Bind the VAO so OpenGL knows to use it
		VAO1.Bind();
		// Draw primitives, number of indices, datatype of indices, index of indices
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}

	// Delete all the objects we've created
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	cuteCatUwU.Delete();
	shaderProgram.Delete();

	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}

