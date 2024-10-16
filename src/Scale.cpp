#include "Scale.h"

Scale::Scale(glm::vec3 scale)
{
    this->scale = scale;
}

glm::mat4 Scale::getModelMatrix()
{
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::scale(model, this->scale);
    return model;
}