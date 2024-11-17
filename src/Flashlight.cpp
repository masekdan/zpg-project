#include "Flashlight.h"

Flashlight::Flashlight(glm::vec3 position, glm::vec3 direction, float angle,glm::vec3 attenuation) : SpotLight(position,direction,angle,attenuation)
{
    this->camera = nullptr;
}

void Flashlight::registerSubject(Subject* subject)
{
    this->camera = static_cast<Camera*>(subject);
}

void Flashlight::update()
{
    this->position = this->camera->getEye();
    this->direction = this->camera->getDirection();
}