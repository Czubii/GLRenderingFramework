#include "objectTransform.h"

Transform::Transform()
{
    pos = glm::vec3(0.0f, 0.0f, 0.0f);
    rot = glm::quat(glm::vec3(0.0f, 0.0f, 0.0f));
    scale = glm::vec3(1.0f, 1.0f, 1.0f);
}

Transform::Transform(const glm::vec3 &_position,
                     const glm::vec3 &_rotation,
                     const glm::vec3 &_scale)
    : pos(_position),
      rot(_rotation),
      scale(_scale) {};
