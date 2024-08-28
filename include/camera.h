#ifndef CAMERA_CLASS
#define CAMERA_CLASS

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include "VBO.h"
#include "objectTransform.h"
#include "shaderClass.h"
#include "mesh.h"

/// @brief Camera class
class Camera
{ 

    public:
        glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
        ///@brief the point at which the camera is looking
        glm::vec3 orientation  = glm::vec3(0.0f, 0.0f, 1.0f);

        Transform transform;

        /// @brief field of view in degrees
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
        Camera(const int & _width, const int & _height, const Transform & _transform = Transform(glm::vec3(0.0f, 0.0f, -2.0f)));

        ///@brief updates containig vertex transformations - perspective and transformation. Call applyMatrix() to update the uniform;
        void updateMatrix();
        
        ///@brief sends vertex transformation matrix to uniform
        void applyMatrix(Shader& shader, const char* uniform) const;

        /// @brief sets new camera dimensions
        void setDimensions(const int & _width, const int & _height);

    private:
        ///@brief matrix containig vertex transformations - perspective and transformation
        glm::mat4 m_matrix = glm::mat4(1.0f);
};



#endif