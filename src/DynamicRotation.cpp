#include "DynamicRotation.h"

DynamicRotation::DynamicRotation(glm::vec3 rot, float speed)
{
    this->rotation = rot;
    this->speed = speed;
    this->angle = 1.0f;

}

float DynamicRotation::rotate(float angle)
{

    if (angle == 360 || angle == 360)
    {
        angle = 0;
    }
    return angle + this->speed;
}

glm::mat4 DynamicRotation::getModelMatrix()
{
    glm::mat4 model = glm::mat4(1.0f);

    this->angle = rotate(this->angle);

    if (rotation.x!=0)
    {
        model = glm::rotate(model, glm::radians(this->angle), glm::vec3(1.0f,0.0f,0.0f));
    }
    else if (rotation.y!=0)
    {
        model = glm::rotate(model, glm::radians(this->angle), glm::vec3(0.0f,1.0f,0.0f));
    }
    else if (rotation.z!=0)
    {
        model = glm::rotate(model, glm::radians(this->angle), glm::vec3(0.0f,0.0f,1.0f));
    }

    return model;
}