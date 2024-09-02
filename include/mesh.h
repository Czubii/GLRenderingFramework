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
#include <debug.h>

class Camera;

enum class DrawMode {
    DEFAULT,
    WIREFRAME,
    LINES
};

class Mesh{

    public:
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    std::vector<Texture> textures;

    VAO VAO;
    Mesh();
    Mesh(const std::vector<Vertex> &_vertices, const std::vector<GLuint> &_indices, const std::vector<Texture> &_textures);
    Mesh(const std::vector<Vertex> &_vertices, const std::vector<GLuint> &_indices, const Texture& _texture);
    Mesh(const std::vector<Vertex> &_vertices, const std::vector<GLuint> &_indices);

    void draw(Shader& shader, const Camera& camera, DrawMode mode = DrawMode::DEFAULT, const Transform& transform = Transform());
    void drawInstanced(Shader& shader, const Camera& camera, GLsizei numInstances, DrawMode mode = DrawMode::DEFAULT);

    private:
    static inline void setVertexShaderUniforms(Shader& shader, const Camera& camera, const Transform& transform = Transform());
};

#endif