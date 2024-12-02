#include "Scene.h"

Scene::Scene(std::vector<ShaderProgram*> &shaders)
{
    camera = Camera::getInstance(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    for (auto s : shaders)
    {
        camera->registerObserver(s);
    }
    this->skybox = nullptr;
}

void Scene::addObject(DrawableObject* obj)
{
    this->objects.push_back(obj);
}

void Scene::setSkybox(std::vector<std::string> faces,ShaderProgram* shader)
{
    this->skybox = new Skybox(faces,shader);
}

void Scene::drawScene()
{
    if (skybox!=nullptr)
    {
        this->skybox->draw(this->camera->getProjection(),this->camera->getView());
    }
    this->camera->matrix(90.0f,0.1f,100.0f);
    for (auto o : this->objects)
    {
        o->draw();
    }
}

void Scene::transform(size_t index, TransformationComponent* transformation)
{
    if (index >= this->objects.size())
    {
        std::cerr << "Object not found" << std::endl;
        exit(-1); 
    }
    this->objects[index]->transform(transformation);
}

Camera* Scene::getCamera()
{
    return this->camera;
}

Scene::~Scene()
{
    for (DrawableObject* dos : this->objects)
    {
        delete dos;
    }
}