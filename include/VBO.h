#ifndef VBO_CLASS
#define VBO_CLASS

#include <glad/glad.h>
#include <vector>
#include <glm.hpp>

// NOTE TO FUTURE SELF:
// if I ever modify this vertex struct remember to also make changes to linking attributes in Mesh class constructor inside mesh.cpp
struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec3 color;
};

class VBO {
public:
    /// @brief VBO's opengl ID
    GLuint ID = 0;

    VBO();

    /// @brief vertex buffer object - stores vertex data in GPU
    /// @param vertices vertices to store
    /// @param size size of vertice array
    VBO(const std::vector<Vertex> &vertices);

    VBO(const std::vector<glm::mat4> &transformations);

    void updateData(const void *newData, GLuint size) const;

    /// @brief Bind this VBO
    void Bind() const;

    /// @brief Unbind the current VBO
    void Unbind() const;

    /// @brief Delete this VBO from gpu memory
    void Delete();
};

#endif
