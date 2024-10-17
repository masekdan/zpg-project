#include "Scene.h"

Scene::Scene(std::vector<ShaderProgram*> shaders)
{
    camera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    for (auto* s : shaders)
    {
        camera->registerShader(s);
    }
}

void Scene::addObject(DrawableObject* obj)
{
    this->objects.push_back(obj);
}

void Scene::drawScene()
{
    this->camera->matrix(45.0f,0.1f,100.0f);
    for (auto o : this->objects)
    {
        o->draw();
    }
}

void Scene::transform(size_t index, TransformationComponent* transformation)
{
    this->objects[index]->transform(transformation);
}