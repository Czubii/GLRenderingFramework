#ifndef CAMERA_CLASS
#define CAMERA_CLASS

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include "VBO.h"
#include "objectTransform.h"
#include "shaderClass.h"
#include "mesh.h"
#include "texture.h"

const Vertex viewMeshVertices[] = 
	{                   //   COORDINATES    /               /      COLORS      /             / TexCoord //
		Vertex{glm::vec3(-0.5f, -0.5f,  0.0f),     glm::vec3(0.83f, 0.70f, 0.44f),	glm::vec2(0.0f, 0.0f)},
        Vertex{glm::vec3(0.5f, -0.5f,  0.0f),     glm::vec3(0.83f, 0.70f, 0.44f),	glm::vec2(0.0f, 0.0f)},
        Vertex{glm::vec3(0.5f, 0.5f,  0.0f),     glm::vec3(0.83f, 0.70f, 0.44f),	glm::vec2(0.0f, 0.0f)},
        Vertex{glm::vec3(-0.5f, 0.5f,  0.0f),     glm::vec3(0.83f, 0.70f, 0.44f),	glm::vec2(0.0f, 0.0f)},

    	Vertex{glm::vec3(-0.5f, 0.5f,  -0.5f),     glm::vec3(0.83f, 0.70f, 0.44f),	glm::vec2(0.0f, 0.0f)},
        Vertex{glm::vec3(0.5f, 0.5f,  -0.5f),     glm::vec3(0.83f, 0.70f, 0.44f),	glm::vec2(0.0f, 0.0f)},
        Vertex{glm::vec3(0.5f, 0.5f,  0.5f),     glm::vec3(0.83f, 0.70f, 0.44f),	glm::vec2(0.0f, 0.0f)},
        Vertex{glm::vec3(-0.5f, 0.5f,  0.5f),     glm::vec3(0.83f, 0.70f, 0.44f),	glm::vec2(0.0f, 0.0f)}
	};

// const GLuint viewMeshIndices[] = {
//     0, 1, 2,
//     2, 3, 0,
//     0, 3, 7,
//     7, 4, 0,
//     0, 1, 5,
//     5, 4, 0,
//     1, 2, 6,
//     6, 5, 1,
//     2, 6, 7,
//     7, 3, 2,
//     4, 5, 6,
//     6, 7, 4

// };
const GLuint viewMeshIndices[] = {
    0, 1, 2,
    2, 3, 0,
};


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

        void drawViewBounds(Shader& shader, const Camera& camera);

        /// @brief sets new camera dimensions
        void setDimensions(const unsigned int & _width, const unsigned int & _height);

    private:
        ///@brief matrix containig vertex transformations - perspective and transformation
        glm::mat4 m_matrix = glm::mat4(1.0f);
        glm::mat4 m_viewBoundsMeshTransformMatrix = glm::mat4(1.0f);//TODO
        Mesh m_viewBoundsMesh;
        void updateViewBoundsMesh();
};



#endif