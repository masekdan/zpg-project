#include "PointLight.h"

PointLight::PointLight(glm::vec3 position,glm::vec3 attenuation)
{
    this->position = position;
    this->attenuation = attenuation;
}

int PointLight::getType()
{
    return 1;
}

glm::vec3 PointLight::getPosition()
{
    return this->position;
}

glm::vec3 PointLight::getAttenuation()
{
    return this->attenuation;
}