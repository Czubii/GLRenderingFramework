#include "EBO.h"

EBO::EBO(std::vector<GLuint>& indices)
{
    // Generate the VBO, and EBO with only 1 object
    glGenBuffers(1, &_ID);

    // Bind the EBO specifying it's a GL_ELEMENT_ARRAY_BUFFER
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ID);
    // Introduce the indices into the EBO
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
}

void EBO::Bind()
{
    // Bind the buffer object to the GL_ELEMENT_ARRAY_BUFFER target,
    // making it the current buffer for vertex attributes.
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ID);
}
void EBO::Unbind()
{
    // Unbind the current buffer from the GL_ELEMENT_ARRAY_BUFFER target to prevent
    // accidental modifications.
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
void EBO::Delete()
{
    // Delete the buffer object, freeing up GPU memory.
    glDeleteBuffers(1, &_ID);
}