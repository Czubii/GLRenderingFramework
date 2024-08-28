#include "camera.h"

Camera::Camera(int _width, int _height, Transform & _transform)
    : width(_width),
      height(_height),
      transform(_transform) {};


void Camera::updateMatrix(Shader &shader, const char *uniform) {
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);

    view = glm::lookAt(transform.pos, transform.rot + transform.pos, m_up);

    if (usePerspective)
    projection = glm::perspective(glm::radians(fovDEG), (float)width/height, nearPlane, farPlane);
    else
    projection = glm::ortho(-width/2.0f, width/2.0f, -height/2.0f, height/2.0f, nearPlane, farPlane);

    GLuint uniID = glGetUniformLocation(shader.ID, uniform);
    glUniformMatrix4fv(uniID, 1, GL_FALSE, glm::value_ptr(projection * view));

};
