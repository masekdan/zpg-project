#include "DrawableObject.h"


DrawableObject::DrawableObject(Model* model, Shader* shader, Transformation* transformation)
{
    this->model = model;
    this->shader = shader;
    this->transformation = transformation;
}


void DrawableObject::draw()
{
    this->shader->Activate();

    glm::mat4 M = transformation->getModelMatrix();

    int modelLoc = this->shader->GetLocation("model");
	glUniformMatrix4fv(modelLoc,1,GL_FALSE,glm::value_ptr(M));

    this->model->drawModel();
}