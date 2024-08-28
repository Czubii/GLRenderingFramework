namespace cube{

#ifndef CUBE_VERTICES
#define CUBE_VERTICES

#include "VBO.h"
#include <glm.hpp>

const Vertex vertices[] = 
	{                   //   COORDINATES    /               /      COLORS      /             / TexCoord //
		Vertex{glm::vec3(-0.5f, -0.5f,  -0.5f),     glm::vec3(0.83f, 0.70f, 0.44f),	glm::vec2(0.0f, 0.0f)},
        Vertex{glm::vec3(0.5f, -0.5f,  -0.5f),     glm::vec3(0.83f, 0.70f, 0.44f),	glm::vec2(0.0f, 0.0f)},
        Vertex{glm::vec3(0.5f, -0.5f,  0.5f),     glm::vec3(0.83f, 0.70f, 0.44f),	glm::vec2(0.0f, 0.0f)},
        Vertex{glm::vec3(-0.5f, -0.5f,  0.5f),     glm::vec3(0.83f, 0.70f, 0.44f),	glm::vec2(0.0f, 0.0f)},

    	Vertex{glm::vec3(-0.5f, 0.5f,  -0.5f),     glm::vec3(0.83f, 0.70f, 0.44f),	glm::vec2(0.0f, 0.0f)},
        Vertex{glm::vec3(0.5f, 0.5f,  -0.5f),     glm::vec3(0.83f, 0.70f, 0.44f),	glm::vec2(0.0f, 0.0f)},
        Vertex{glm::vec3(0.5f, 0.5f,  0.5f),     glm::vec3(0.83f, 0.70f, 0.44f),	glm::vec2(0.0f, 0.0f)},
        Vertex{glm::vec3(-0.5f, 0.5f,  0.5f),     glm::vec3(0.83f, 0.70f, 0.44f),	glm::vec2(0.0f, 0.0f)},
	};

#endif

#ifndef CUBE_INDICES
#define CUBE_INDICES

#include "VBO.h"
#include <glad/glad.h>

const GLuint indices[] = {
    0, 1, 2,
    2, 3, 0,
    0, 3, 7,
    7, 4, 0,
    0, 1, 5,
    5, 4, 0,
    1, 2, 6,
    6, 5, 1,
    2, 6, 7,
    7, 3, 2,
    4, 5, 6,
    6, 7, 4

};


#endif

}