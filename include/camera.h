#ifndef CAMERA_CLASS
#define CAMERA_CLASS

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include "objectTransform.h"
#include "shaderClass.h"


class Camera
{
    private:

        glm::vec3 m_up = glm::vec3(0.0f, 1.0f, 0.0f);

    public:
        Transform & transform;

        /// @brief field of view in radians
        float fovDEG = 80.0f;

        float nearPlane = 0.1f; //min render distance
        float farPlane = 100.0f; //max render distance

        // window size
        int width;
        int height;

        bool usePerspective = true;

        /// @brief sets basic parameters
        /// @param _width projection width
        /// @param _height projection height
        /// @param _transform camera position as reference
        Camera(int _width, int _height, Transform & _transform);


        void updateMatrix(Shader & shader, const char* uniform);


};



#endif