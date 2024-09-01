#ifndef MESH_CLASS
#define MESH_CLASS

#include <vector>
#include "VBO.h"
#include "texture.h"
#include "VAO.h"
#include "EBO.h"
#include "objectTransform.h"
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

class Camera;
class Mesh{

    public:
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    std::vector<Texture> textures;

    VAO VAO;

    Mesh();
    Mesh(std::vector<Vertex> &_vertices, std::vector<GLuint> &_indices, std::vector<Texture> &_textures);
    Mesh(std::vector<Vertex> &_vertices, std::vector<GLuint> &_indices, Texture& _texture);
    Mesh(std::vector<Vertex> &_vertices, std::vector<GLuint> &_indices);

    void draw(Shader& shader, const Camera& camera, const Transform& transform = Transform());

    void drawWireframe(Shader& shader, const Camera& camera, const Transform& transform = Transform());
    
    /// @note won't work well if mesh isn't created specifically for this use case
    void drawContour(Shader& shader, const Camera& camera, const Transform& transform = Transform());

    private:
    inline void setVertexShaderUniforms(Shader& shader, const Camera& camera, const Transform& transform);
};

#endif