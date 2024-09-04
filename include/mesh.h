#ifndef MESH_CLASS
#define MESH_CLASS

#include <vector>
#include "VBO.h"
#include "VAO.h"
#include "shaderClass.h"
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
    glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);//TODO: replace with a material class
    std::string name;

    VAO VAO;
    Mesh();
    Mesh(const std::vector<Vertex> &_vertices, const std::vector<GLuint> &_indices, const glm::vec3& _color, const char* _name = "unnamedMesh");

    void draw(Shader& shader, const Camera& camera, DrawMode mode = DrawMode::DEFAULT, const Transform& transform = Transform());
    void drawInstanced(Shader& shader, const Camera& camera, GLsizei numInstances, DrawMode mode = DrawMode::DEFAULT);

    private:
    inline void setVertexShaderUniforms(Shader& shader, const Camera& camera, const Transform& transform = Transform()) const;
};

#endif