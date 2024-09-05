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

class Mesh {
public:
    std::vector<Vertex> vertices;
    std::string name;

    VAO VAO;

    Mesh();

    Mesh(const std::vector<Vertex> &_vertices, const char *_name = "unnamedMesh");

    void draw(Shader &shader, const Camera &camera, DrawMode mode = DrawMode::DEFAULT,
              const Transform &transform = Transform());

    void drawInstanced(Shader &shader, const Camera &camera, GLsizei numInstances, DrawMode mode = DrawMode::DEFAULT);

private:
    inline void setVertexShaderUniforms(Shader &shader, const Camera &camera,
                                        const Transform &transform = Transform()) const;
};

#endif
