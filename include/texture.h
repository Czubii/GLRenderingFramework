#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H

#include <glad/glad.h>
#include "shaderClass.h"
#include "glm.hpp"

class Texture{

public: 
    GLuint ID;
    GLenum type;


    /**
    * @brief Loads and creates a texture from an image file.
    * 
    * @param imageSrc Path to the image file.
    * @param texType Type of texture (e.g., GL_TEXTURE_2D).
    * @param slot Texture slot (e.g., GL_TEXTURE0).
    * @param format Pixel data format (e.g., GL_RGBA).
    * @param pixelType Pixel data type (e.g., GL_UNSIGNED_BYTE).
    */
    Texture(const char* imageSrc, GLenum texType, GLenum slot, GLenum format, GLenum pixelType);

    /// @brief creates 1x1 texture with a specified RGB / RGBA color
    /// @param R red
    /// @param G green
    /// @param B blue
    /// @param A alpha
    Texture(const unsigned char &R,
			const unsigned char &G,
			const unsigned char &B,
			const unsigned char &A = 255);

    /**
    * @brief Assigns the texture to a shader uniform.
    * 
    * @param shader Shader program.
    * @param uniform Uniform name in the shader.
    * @param unit Texture unit (e.g., 0 for GL_TEXTURE0).
    */
    void texUnit(Shader &shader, const char* uniform, GLuint unit);

    /**
    * @brief Binds the texture for use.
    */
    void Bind();


    /**
    * @brief Unbinds the texture.
    */
    void Unbind();

    /**
    * @brief Deletes the texture.
    */
    void Delete();

    private:

};

#endif
