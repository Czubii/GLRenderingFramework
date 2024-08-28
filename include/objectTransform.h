#ifndef TRANSFORM_CLASS
#define TRANSFORM_CLASS

#include <glm.hpp>

class Transform
{
    public:
        glm::vec3 pos;
        glm::vec3 rot;
        glm::vec3 scale;

    Transform();
    Transform(glm::vec3 _position, glm::vec3 _rotation, glm::vec3 _scale);
};

#endif