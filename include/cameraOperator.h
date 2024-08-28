#ifndef CAMERA_OPERATOR_CLASS
#define CAMERA_OPERATOR_CLASS

#define GLM_ENABLE_EXPERIMENTAL

#include "camera.h"
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtx/rotate_vector.hpp>
#include <gtx/vector_angle.hpp>


class CameraOperator
{
private:
    Camera *m_camera;
    bool m_firstClick = true;

public:
    float speed = 0.1f;
    float sensitivity = 100.0f;

    CameraOperator(Camera *_camera);

    void handleInputs(GLFWwindow *window, const float timeDelta);

    void setCamera(Camera *_camera);
    Camera &getCamera();
};

#endif
