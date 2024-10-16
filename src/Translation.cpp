#include "Translation.h"


Translation::Translation(glm::vec3 pos)
{
    this->position = pos;
}

glm::mat4 Translation::getModelMatrix()
{
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    return model;
}