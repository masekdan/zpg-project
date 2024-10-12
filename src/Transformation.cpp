#include "Transformation.h"


Transformation::Transformation()
{
    model = glm::mat4(1.0f);
}

void Transformation::rotate(float angle)
{
    this->model = glm::rotate(this->model,glm::radians(angle),glm::vec3(0.0f,1.0f,0.0f));
}
    
void Transformation::scale(float scale)
{

}
void Transformation::translate(float direction)
{

}

glm::mat4 Transformation::getModelMatrix()
{
    return this->model;
}