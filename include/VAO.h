#ifndef VAO_CLASS
#define VAO_CLASS

#include <glad/glad.h>
#include "VBO.h"

class VAO
{

public:
    /// @brief VAO's opengl ID
    GLuint _ID;
    VAO();

    void VAO::LinkAttrib(VBO VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);


    /// @brief Bind this VAO
    void Bind();

    /// @brief Unbind the current VAO
    void Unbind();

    /// @brief Delete this VAO from gpu memory
    void Delete();
};

#endif