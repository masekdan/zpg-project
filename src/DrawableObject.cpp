#include "DrawableObject.h"


DrawableObject::DrawableObject(Model* model, ShaderProgram* shader, TransformationComponent* transformation)
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

    this->shader->SetUniform("model",M);

    this->model->drawModel();
}

void DrawableObject::transform(TransformationComponent* transformation)
{
    this->transformation = transformation;
}


DrawableObject* DrawableObjectFactory::create(Model* model, ShaderProgram* shader, TransformationComponent* transformation)
{
    return new DrawableObject(model,shader,transformation);
}