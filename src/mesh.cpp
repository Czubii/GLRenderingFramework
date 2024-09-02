#include "mesh.h"
#include "camera.h"
#include "iostream"

Mesh::Mesh() {
}

Mesh::Mesh(const std::vector<Vertex> &_vertices, const std::vector<GLuint> &_indices,
           const std::vector<Texture> &_textures)
    : vertices(_vertices),
      indices(_indices),
      textures(_textures) {
    VAO.Bind();

    VBO VBO(vertices);
    EBO EBO(indices);

    //modify the bellow lines if I ever change the Vertex struct
    VAO.LinkAttrib(VBO, 0, 3, GL_FLOAT, 8 * sizeof(float), (void *) 0);
    VAO.LinkAttrib(VBO, 1, 3, GL_FLOAT, 8 * sizeof(float), (void *) (3 * sizeof(float)));
    VAO.LinkAttrib(VBO, 2, 2, GL_FLOAT, 8 * sizeof(float), (void *) (6 * sizeof(float)));

    VAO.Unbind();
    VBO.Unbind();
    EBO.Unbind();
}

Mesh::Mesh(const std::vector<Vertex> &_vertices, const std::vector<GLuint> &_indices, const Texture &_texture)
    : Mesh(_vertices, _indices, std::vector<Texture>{_texture}) {}

Mesh::Mesh(const std::vector<Vertex> &_vertices, const std::vector<GLuint> &_indices)
    : Mesh(_vertices, _indices, std::vector<Texture>()) {}


void Mesh::draw(Shader &shader, const Camera &camera, const DrawMode mode, const Transform &transform)
//TODO: add the multiple textures functionality
{
    shader.Activate();
    VAO.Bind();
    setVertexShaderUniforms(shader, camera, transform);

    if (!textures.empty()) {//TODO: add default texture
        textures[0].texUnit(shader, "tex0", 0);
        textures[0].Bind();
    }

    switch (mode) {
        default:
            glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, 0);

        case (DrawMode::WIREFRAME):
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, 0);
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        case(DrawMode::LINES):
            glEnable(GL_LINE_SMOOTH);
            glLineWidth(2.0f);
            glDrawElements(GL_LINE_LOOP, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, 0);
            glDisable(GL_LINE_SMOOTH);
    }
}

void Mesh::drawInstanced(Shader &shader, const Camera &camera, const GLsizei numInstances, DrawMode mode) {
    shader.Activate();
    VAO.Bind();
    setVertexShaderUniforms(shader, camera);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glDrawElementsInstanced(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, 0, numInstances);

    GL_CHECK_ERROR();

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

inline void Mesh::setVertexShaderUniforms(Shader &shader, const Camera &camera, const Transform &transform) {
    camera.applyMatrix(shader, "cameraMatrix");

    auto translation = glm::mat4(1.0f);
    auto scale = glm::mat4(1.0f);

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
