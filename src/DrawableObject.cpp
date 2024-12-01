#include "DrawableObject.h"


DrawableObject::DrawableObject(Model* model, ShaderProgram* shader, TransformationComponent* transformation, std::vector<Light*> lights, Material* material)
{
    this->model = model;
    this->shader = shader;
    this->transformation = transformation;
    this->lights = lights;
    this->material = material;
}


void DrawableObject::draw()
{
    
    glm::mat4 M = transformation->getModelMatrix();
    glm::mat4 V = glm::mat4(1.0f);
    glm::mat4 P = glm::mat4(1.0f);


    this->shader->Activate();
    this->shader->SetUniform("model",M);
    this->shader->SetMaterial(this->material);
    this->shader->SetLights(this->lights);

    if (this->model->hasTextureMet())
    {
        shader->SetUniform("ourTexture", 0);
    }
    this->model->drawModel();
    
    glUseProgram(0);
    //this->shader->Deactivate();
}

void DrawableObject::transform(TransformationComponent* transformation)
{
    this->transformation = transformation;
}


DrawableObject* DrawableObjectFactory::create(Model* model, ShaderProgram* shader, TransformationComponent* transformation,std::vector<Light*> lights,Material* material)
{
    return new DrawableObject(model,shader,transformation,lights,material);
}

DrawableObject::~DrawableObject()
{
    delete this->transformation;
}