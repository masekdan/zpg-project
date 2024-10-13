#include "Transformation.h"


Transformation::Transformation(glm::vec3 pos, glm::vec3 rot, float sc)
{
    this->position = pos;
    this->rotation = rot;
    this->scale = sc;
}


glm::mat4 Transformation::getModelMatrix()
{
    glm::mat4 model = glm::mat4(1.0f);

    model = glm::translate(model, position);
    model = glm::rotate(model, rotation.x, glm::vec3(1.0f,0.0f,0.0f));
    model = glm::rotate(model, rotation.y, glm::vec3(0.0f,1.0f,0.0f));
    model = glm::rotate(model, rotation.z, glm::vec3(0.0f,0.0f,1.0f));
    model = glm::scale(model, glm::vec3(scale));

    return model;
}