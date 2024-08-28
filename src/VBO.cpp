#include "VBO.h"

VBO::VBO(std::vector<Vertex> &vertices)
{

    // Generate the VBO, with only 1 object
    glGenBuffers(1, &_ID);
    // Bind the VBO specifying it's a GL_ARRAY_BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, _ID);
	// Introduce the vertices into the VBO
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);//TODO: GL_STATIC_DRAW - look into this for future self
}
void VBO::Bind()
{
    // Bind the buffer object to the GL_ARRAY_BUFFER target,
    // making it the current buffer for vertex attributes.
    glBindBuffer(GL_ARRAY_BUFFER, _ID);
}
void VBO::Unbind()
{
    // Unbind the current buffer from the GL_ARRAY_BUFFER target to prevent
    // accidental modifications.
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
void VBO::Delete()
{
    // Delete the buffer object, freeing up GPU memory.
    glDeleteBuffers(1, &_ID);
}