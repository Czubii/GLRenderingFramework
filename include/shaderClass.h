#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include<glad/glad.h>
#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
#include<cerrno>

/// @brief Reads a text file and outputs a string with everything in the text file
/// @param filename name of the file to read
/// @return string containing data from file
std::string get_file_contents(const char* filename);


/// @brief class to build and store the shader program
class Shader
{
public:
	/// Reference ID of the Shader Program
	GLuint ID;
	
	/// @brief Constructor that build the Shader Program from 2 different shaders
	/// @param vertexFile path to vertex shader
	/// @param fragmentFile path to fragment shader
	Shader(const char* vertexFile, const char* fragmentFile);

	/// @brief Activates the Shader Program telling opengl to use it
	void Activate();
	/// @brief Deletes the Shader Program
	void Delete();

private:

	/// @brief Prints eventual shader compile errors to console
	static void compileErrors(unsigned int shader, const char* type);
};

#endif
