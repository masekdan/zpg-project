#include "DrawableObject.h"


DrawableObject::DrawableObject(Model* model, Shader* shader, TransformationComponent* transformation)
{
    this->model = model;
    this->shader = shader;
    this->transformation = transformation;
}


void DrawableObject::draw()
{
    this->shader->Activate();

    glm::mat4 M = transformation->getModelMatrix();
    glm::mat4 V = glm::mat4(1.0f);
    glm::mat4 P = glm::mat4(1.0f);

    int modelLoc = this->shader->GetLocation("model");
	glUniformMatrix4fv(modelLoc,1,GL_FALSE,glm::value_ptr(M));

    this->model->drawModel();
}


DrawableObject* DrawableObjectFactory::create(Model* model, Shader* shader, TransformationComponent* transformation)
{
    return new DrawableObject(model,shader,transformation);
}