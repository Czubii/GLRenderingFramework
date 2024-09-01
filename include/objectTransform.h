#ifndef TRANSFORM_CLASS
#define TRANSFORM_CLASS

#define GLM_ENABLE_EXPERIMENTAL
#include <glm.hpp>
#include <gtx/quaternion.hpp>

class Transform
{
public:
    glm::vec3 pos;
    glm::quat rot;
    glm::vec3 scale;

    Transform();
    Transform(const glm::vec3 &_position,
              const glm::vec3 &_rotation = glm::vec3(),
              const glm::vec3 &_scale= glm::vec3(1.0f, 1.0f, 1.0f));
};

#endif