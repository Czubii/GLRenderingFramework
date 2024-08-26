#ifndef EBO_CLASS
#define EBO_CLASS

#include <glad/glad.h>
class EBO
{
public:
    /// @brief EBO's opengl ID
    GLuint _ID;

    /// @brief element buffer object - Stores indices that define the order of vertex rendering, allowing reuse of vertex data.
    /// @param indices indices to store
    /// @param size size of indice array
    EBO(GLuint* indices, GLsizeiptr size);

    /// @brief Bind this EBO
    void Bind();

    /// @brief Unbind the current EBO
    void Unbind();

    /// @brief Delete this EBO from gpu memory
    void Delete();
};

#endif