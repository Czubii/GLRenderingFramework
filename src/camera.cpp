#include "camera.h"


Camera::Camera(const int & _width, const int & _height, const Transform & _transform)
    : transform(_transform),
      width(_width),
      height(_height) {};


void Camera::updateMatrix() {
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);

    view = glm::lookAt(transform.pos, orientation + transform.pos, up);
    if (usePerspective)
    projection = glm::perspective(glm::radians(fovDEG), static_cast<float>(width)/height, nearPlane, farPlane);
    else
    projection = glm::ortho(-width/2.0f, width/2.0f, -height/2.0f, height/2.0f, nearPlane, farPlane); //TODO orthographic view

    m_matrix = (projection * view);
}
void Camera::applyMatrix(Shader &shader, const char *uniform) const
{
    GLuint uniID = glGetUniformLocation(shader.ID, uniform);
    glUniformMatrix4fv(uniID, 1, GL_FALSE, glm::value_ptr(m_matrix));
}
void Camera::setDimensions(const int &_width, const int &_height) //FIXME: currently resizing camera also changes fov. make the render dimensions static and apply some matrix
{
    width = _width;
    height = _height;
    updateMatrix();
}

