#include "VBO.h"

VBO::VBO() {
    glGenBuffers(1, &ID);
}

VBO::VBO(std::vector<Vertex> &vertices)
{

    // Generate the VBO, with only 1 object
    glGenBuffers(1, &ID);
    // Bind the VBO specifying it's a GL_ARRAY_BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	// Introduce the vertices into the VBO
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);//TODO: GL_STATIC_DRAW - look into this for future self

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

VBO::VBO(const std::vector<glm::mat4> &transformations) {
    // Generate the VBO, with only 1 object
    glGenBuffers(1, &ID);
    // Bind the VBO specifying it's a GL_ARRAY_BUFFER
    glBindBuffer(GL_ARRAY_BUFFER, ID);
    // Introduce the vertices into the VBO
    glBufferData(GL_ARRAY_BUFFER, transformations.size() * sizeof(glm::mat4), transformations.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::updateData(const void* newData, const GLuint size) const {
    Bind();

    glBufferData(GL_ARRAY_BUFFER, size, newData, GL_STATIC_DRAW);

    Unbind();
}

void VBO::Bind() const
{
    // Bind the buffer object to the GL_ARRAY_BUFFER target,
    // making it the current buffer for vertex attributes.
    glBindBuffer(GL_ARRAY_BUFFER, ID);
}
void VBO::Unbind() const
{
    // Unbind the current buffer from the GL_ARRAY_BUFFER target to prevent
    // accidental modifications.
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
void VBO::Delete()
{
    // Delete the buffer object, freeing up GPU memory.
    glDeleteBuffers(1, &ID);
}