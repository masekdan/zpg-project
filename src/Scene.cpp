#include "Scene.h"

Scene::Scene()
{
    
}

void Scene::addObject(DrawableObject* obj)
{
    this->objects.push_back(obj);
}

void Scene::drawScene()
{
    for (auto o : this->objects)
    {
        o->draw();
    }
}