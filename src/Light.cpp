#include "Light.h"

Light::Light(glm::vec3 pos)
{
    this->position = pos;
}

glm::vec3 Light::getPosition()
{
    return this->position;
}