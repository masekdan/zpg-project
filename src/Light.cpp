#include "Light.h"

Light::Light(glm::vec3 pos,glm::vec3 attenuation)
{
    this->position = pos;
    this->attenuation = attenuation;
}

glm::vec3 Light::getPosition()
{
    return this->position;
}

glm::vec3 Light::getAttenuation()
{
    return this->attenuation;
}