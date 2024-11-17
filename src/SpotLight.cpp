#include "SpotLight.h"

SpotLight::SpotLight(glm::vec3 position, glm::vec3 direction, float angle,glm::vec3 attenuation)
{
    this->position = position;
    this->direction = direction;
    this->angle = angle;
    this->attenuation = attenuation;
}

int SpotLight::getType()
{
    return 3;
}

glm::vec3 SpotLight::getDirection()
{
    return this->direction;
}

glm::vec3 SpotLight::getPosition()
{
    return this->position;
}

glm::vec3 SpotLight::getAttenuation()
{
    return this->attenuation;
}

float SpotLight::getAngle()
{
    return glm::cos(glm::radians(this->angle));
}