#include "DrawableObject.h"


DrawableObject::DrawableObject(Model* model, ShaderProgram* shader, TransformationComponent* transformation, Light* light)
{
    this->model = model;
    this->shader = shader;
    this->transformation = transformation;
    this->light = light;
}


void DrawableObject::draw()
{
    this->shader->Activate();

    glm::mat4 M = transformation->getModelMatrix();
    glm::mat4 V = glm::mat4(1.0f);
    glm::mat4 P = glm::mat4(1.0f);


    this->shader->SetUniform("model",M);
    this->shader->SetUniform("lightPosition",this->light->getPosition());

    
    this->model->drawModel();
    //this->shader->Deactivate();
}

void DrawableObject::transform(TransformationComponent* transformation)
{
    this->transformation = transformation;
}


DrawableObject* DrawableObjectFactory::create(Model* model, ShaderProgram* shader, TransformationComponent* transformation,Light* light)
{
    return new DrawableObject(model,shader,transformation,light);
}

DrawableObject::~DrawableObject()
{
    delete this->transformation;
}