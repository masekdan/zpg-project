#include "DynamicRotation.h"

DynamicRotation::DynamicRotation(glm::vec3 rot, float speed)
{
    this->rotation = rot;
    this->speed = speed;
}

float DynamicRotation::rotate(float angle)
{
    return angle + this->speed;
}

glm::mat4 DynamicRotation::getModelMatrix()
{
    glm::mat4 model = glm::mat4(1.0f);

    model = glm::rotate(model, glm::radians(rotate(rotation.x)), glm::vec3(1.0f,0.0f,0.0f));
    model = glm::rotate(model, glm::radians(rotate(rotation.y)), glm::vec3(0.0f,1.0f,0.0f));
    model = glm::rotate(model, glm::radians(rotate(rotation.z)), glm::vec3(0.0f,0.0f,1.0f));

    return model;
}