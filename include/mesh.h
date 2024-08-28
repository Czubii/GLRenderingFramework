#ifndef MESH_CLASS
#define MESH_CLASS

#include <vector>
#include "VBO.h"
#include "texture.h"
#include "camera.h"
#include "VAO.h"
#include "EBO.h"

class Mesh{

    public:
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    std::vector<Texture> textures;

    VAO VAO;

    Mesh(std::vector<Vertex> &_vertices, std::vector<GLuint> &_indices, std::vector<Texture> &_textures);

    void draw(Shader shader, Camera camera);

    void drawWireframe(Shader shader, Camera camera);
};

#endif