#ifndef VBO_CLASS
#define VBO_CLASS

#include <glad/glad.h>
class VBO
{
public:
    /// @brief VBO's opengl ID
    GLuint _ID;

    /// @brief vertex buffer object - stores vertex data in GPU
    /// @param vertices vertices to store
    /// @param size size of vertice array
    VBO(GLfloat* vertices, GLsizeiptr size);

    /// @brief Bind this VBO
    void Bind();

    /// @brief Unbind the current VBO
    void Unbind();

    /// @brief Delete this VBO from gpu memory
    void Delete();
};

#endif