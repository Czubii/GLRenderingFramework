#include "camera.h"


Camera::Camera(const int & _width, const int & _height, const Transform & _transform)
    : width(_width),
      height(_height),
      transform(_transform) {
        updateViewBoundsMesh();
      };


void Camera::updateMatrix() {
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);

    view = glm::lookAt(transform.pos, orientation + transform.pos, up);
    if (usePerspective)
    projection = glm::perspective(glm::radians(fovDEG), (float)width/height, nearPlane, farPlane);
    else
    projection = glm::ortho(-width/2.0f, width/2.0f, -height/2.0f, height/2.0f, nearPlane, farPlane); //TODO

    m_matrix = (projection * view);
}
void Camera::applyMatrix(Shader &shader, const char *uniform) const
{
    GLuint uniID = glGetUniformLocation(shader.ID, uniform);
    glUniformMatrix4fv(uniID, 1, GL_FALSE, glm::value_ptr(m_matrix));
}
void Camera::drawViewBounds(Shader &shader, const Camera &camera) 
{
    m_viewBoundsMesh.draw(shader, camera, DrawMode::LINES, transform);
}
void Camera::setDimensions(const unsigned int &_width, const unsigned int &_height) //FIXME: currentl resizing camera also changes fov. make the render dimensions static and apply some matrix 
{
    width = _width;
    height = _height;
    updateViewBoundsMesh();
    updateMatrix();
}
void Camera::updateViewBoundsMesh()
{
    std::vector<Vertex> vertices = std::vector<Vertex>(std::begin(viewMeshVertices), std::end(viewMeshVertices));
    std::vector<GLuint> indices = std::vector<GLuint>(std::begin(viewMeshIndices), std::end(viewMeshIndices));
    m_viewBoundsMesh = Mesh(vertices, indices, Texture(211, 81, 64, 100));
};
