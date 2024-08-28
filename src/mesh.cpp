#include "mesh.h"

Mesh::Mesh(std::vector<Vertex> &_vertices, std::vector<GLuint> &_indices, std::vector<Texture> &_textures)
    : vertices(_vertices),
      indices(_indices),
      textures(_textures)
{
    VAO.Bind();

    VBO VBO(vertices);
    EBO EBO(indices);

    //modify the bellow lines if I ever change the Vertex struct
    VAO.LinkAttrib(VBO, 0, 3, GL_FLOAT, 8 * sizeof(float), (void *)0);
	VAO.LinkAttrib(VBO, 1, 3, GL_FLOAT, 8 * sizeof(float), (void *)(3 * sizeof(float)));
	VAO.LinkAttrib(VBO, 2, 2, GL_FLOAT, 8 * sizeof(float), (void *)(6 * sizeof(float)));

    VAO.Unbind();
	VBO.Unbind();
	EBO.Unbind();
}

void Mesh::draw(Shader shader, Camera camera)//TODO: add the multiple textures functionality
{
	shader.Activate();
	VAO.Bind();
    camera.updateMatrix(shader, "cameraMatrix");

    textures[0].texUnit(shader, "tex0", 0);
    textures[0].Bind();
	// Draw the actual mesh
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

    
}

void Mesh::drawWireframe(Shader shader, Camera camera)
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    shader.Activate();
	VAO.Bind();
    camera.updateMatrix(shader, "cameraMatrix");
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
