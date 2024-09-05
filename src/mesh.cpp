#include "mesh.h"
#include "camera.h"
#include "iostream"

Mesh::Mesh() = default;

Mesh::Mesh(const std::vector<Vertex> &_vertices, const char *_name)
    : vertices(_vertices),
      name(_name) {
    VAO.Bind();

    VBO VBO(vertices);

    //modify the bellow lines if I ever change the Vertex struct
    VAO.LinkAttrib(VBO, 0, 3, GL_FLOAT, 9 * sizeof(float), nullptr);
    VAO.LinkAttrib(VBO, 1, 3, GL_FLOAT, 9 * sizeof(float), reinterpret_cast<void *>(3 * sizeof(float)));
    VAO.LinkAttrib(VBO, 2, 3, GL_FLOAT, 9 * sizeof(float), reinterpret_cast<void *>(6 * sizeof(float)));

    VAO.Unbind();
    VBO.Unbind();
}

void Mesh::draw(Shader &shader, const Camera &camera, const DrawMode mode, const Transform &transform) {
    shader.Activate();
    VAO.Bind();
    setVertexShaderUniforms(shader, camera, transform);
    switch (mode) {
        default:
            glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(vertices.size()));
            break;

        case (DrawMode::WIREFRAME):
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(vertices.size()));
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            break;

        case(DrawMode::LINES):
            glEnable(GL_LINE_SMOOTH);
            glLineWidth(2.0f);
            glDrawArrays(GL_LINE_LOOP, 0, static_cast<GLsizei>(vertices.size()));
            glDisable(GL_LINE_SMOOTH);
            break;
    }
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
}
