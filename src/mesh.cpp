#include "mesh.h"
#include "camera.h"
#include "iostream"

Mesh::Mesh() = default;

Mesh::Mesh(const std::vector<Vertex> &_vertices, const std::vector<GLuint> &_indices,
           const GLubyte _color[4])
    : vertices(_vertices),
      indices(_indices) {
    color[0] = _color[0];
    color[1] = _color[1];
    color[2] = _color[2];
    color[3] = _color[3];
    VAO.Bind();

    VBO VBO(vertices);
    EBO EBO(indices);

    //modify the bellow lines if I ever change the Vertex struct
    VAO.LinkAttrib(VBO, 0, 3, GL_FLOAT, 3 * sizeof(float), nullptr);

    VAO.Unbind();
    VBO.Unbind();
    EBO.Unbind();
}

void Mesh::draw(Shader &shader, const Camera &camera, const DrawMode mode, const Transform &transform) {
    shader.Activate();
    VAO.Bind();
    setVertexShaderUniforms(shader, camera, transform);

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

inline void Mesh::setVertexShaderUniforms(Shader &shader, const Camera &camera, const Transform &transform) const {
    camera.applyMatrix(shader, "cameraMatrix");

    auto translation = glm::mat4(1.0f);
    auto scale = glm::mat4(1.0f);

    translation = glm::translate(translation, transform.pos);
    glm::mat4 rotation = glm::toMat4(transform.rot);
    scale = glm::scale(scale, transform.scale);

    const GLint translationUni = glGetUniformLocation(shader.ID, "translation");
    glUniformMatrix4fv(translationUni, 1, GL_FALSE, glm::value_ptr(translation));

    const GLint rotationUni = glGetUniformLocation(shader.ID, "rotation");
    glUniformMatrix4fv(rotationUni, 1, GL_FALSE, glm::value_ptr(rotation));

    const GLint scaleUni = glGetUniformLocation(shader.ID, "scale");
    glUniformMatrix4fv(scaleUni, 1, GL_FALSE, glm::value_ptr(scale));

    const auto colorF = glm::vec4(color[0] / 255.0f, color[1] / 255.0f, color[2] / 255.0f, color[3] / 255.0f);
    const GLint colorUni = glGetUniformLocation(shader.ID, "objectColor");
    glUniform4fv(colorUni, 4, glm::value_ptr(colorF));
}
