#include "objectTransform.h"

Transform::Transform()
{
    pos = glm::vec3(0.0f, 0.0f, 0.0f);
    rot = glm::vec3(0.0f, 0.0f, 0.0f);
    scale = glm::vec3(1.0f, 1.0f, 1.0f);
}

Transform::Transform(glm::vec3 _position, glm::vec3 _rotation, glm::vec3 _scale) : pos(_position),
                                                                                   rot(_rotation),
                                                                                   scale(_scale) {};
