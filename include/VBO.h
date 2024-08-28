#ifndef VBO_CLASS
#define VBO_CLASS

#include <glad/glad.h>
#include <vector>
#include <glm.hpp>

// NOTE TO FUTURE SELF:
// if I ever modify this vertex struct remember to also make changes to linking atributes in Mesh class constructor inside mesh.cpp
struct Vertex{
    glm::vec3 position;
    glm::vec3 color;
    glm::vec2 textureUV;
};

class VBO
{
public:
    /// @brief VBO's opengl ID
    GLuint _ID;

    /// @brief vertex buffer object - stores vertex data in GPU
    /// @param vertices vertices to store
    /// @param size size of vertice array
    VBO(std::vector<Vertex>& vertices);

    /// @brief Bind this VBO
    void Bind();

    /// @brief Unbind the current VBO
    void Unbind();

    /// @brief Delete this VBO from gpu memory
    void Delete();
};

#endif