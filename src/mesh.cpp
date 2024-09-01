#include "mesh.h"
#include "camera.h"
#include "iostream"

Mesh::Mesh(){}

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

Mesh::Mesh(std::vector<Vertex> &_vertices, std::vector<GLuint> &_indices, Texture &_texture)
:Mesh(_vertices, _indices, std::vector<Texture>{_texture}){}
Mesh::Mesh(std::vector<Vertex> &_vertices, std::vector<GLuint> &_indices)
:Mesh(_vertices, _indices, std::vector<Texture>()){}


void Mesh::draw(Shader& shader, const Camera& camera, const Transform& transform)//TODO: add the multiple textures functionality
{
	shader.Activate();
	VAO.Bind();
    
    setVertexShaderUniforms(shader, camera, transform);

    if(textures.size() > 0){
        textures[0].texUnit(shader, "tex0", 0);
        textures[0].Bind();
    }
	// Draw the actual mesh
	glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, 0);


    
}

void Mesh::drawWireframe(Shader& shader, const Camera& camera, const Transform& transform)//TODO: consider adding model matrix as parameter
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    shader.Activate();
	VAO.Bind();

    setVertexShaderUniforms(shader, camera, transform);

    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, 0);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void Mesh::drawContour(Shader &shader, const Camera &camera, const Transform &transform)
{
    glEnable(GL_LINE_SMOOTH);
    glLineWidth(2.0f);
    shader.Activate();
	VAO.Bind();

    setVertexShaderUniforms(shader, camera, transform);

    if(textures.size() > 0){
        textures[0].texUnit(shader, "tex0", 0);
        textures[0].Bind();
    }

    glDrawElements(GL_LINE_LOOP, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, 0);
    glDisable(GL_LINE_SMOOTH);
}

inline void Mesh::setVertexShaderUniforms(Shader &shader, const Camera &camera, const Transform &transform)
{
    camera.applyMatrix(shader, "cameraMatrix");

    glm::mat4 translation = glm::mat4(1.0f);
    glm::mat4 scale = glm::mat4(1.0f);

    translation = glm::translate(translation, transform.pos);
    glm::mat4 rotation = glm::toMat4(transform.rot);
    scale = glm::scale(scale, transform.scale);

    GLuint translationUni = glGetUniformLocation(shader.ID, "translation");
    glUniformMatrix4fv(translationUni, 1, GL_FALSE, glm::value_ptr(translation));

    GLuint rotationUni = glGetUniformLocation(shader.ID, "rotation");
    glUniformMatrix4fv(rotationUni, 1, GL_FALSE, glm::value_ptr(rotation));

    GLuint scaleUni = glGetUniformLocation(shader.ID, "scale");
    glUniformMatrix4fv(scaleUni, 1, GL_FALSE, glm::value_ptr(scale));
}
