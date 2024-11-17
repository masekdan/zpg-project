#include "DirectionLight.h"

DirectionLight::DirectionLight(glm::vec3 direction)
{
    this->direction = direction;
}

int DirectionLight::getType()
{
    return 2;
}

glm::vec3 DirectionLight::getDirection()
{
    return this->direction;
}