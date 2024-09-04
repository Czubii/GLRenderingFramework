#ifndef CAMERA_OPERATOR_CLASS
#define CAMERA_OPERATOR_CLASS

#define GLM_ENABLE_EXPERIMENTAL

#include "camera.h"
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtx/rotate_vector.hpp>
#include <gtx/vector_angle.hpp>
#include <gtx/quaternion.hpp>

#define OPERATOR_SPEED 14.0f
#define OPERATOR_SPEED_SHIFT_KEY 30.0f

class CameraOperator {
private:
    Camera *m_camera;
    bool m_firstClick = true;

public:
    float speed = 0.4f;
    float sensitivity = 100.0f;

    CameraOperator(Camera *_camera);

    void handleInputs(GLFWwindow *window, const float timeDelta);

    void setCamera(Camera *_camera);

    Camera &getCamera();
};

#endif
