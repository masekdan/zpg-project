#ifndef SCENE_CLASS_H
#define SCENE_CLASS_H

#include "DrawableObject.h"
#include "Camera.h"
#include "ShaderProgram.h"
#include "Skybox.h"

#include <vector>
#include <glm/vec3.hpp>

class Scene
{
private:
    std::vector<DrawableObject*> objects;
    Camera* camera;
    Skybox* skybox;
public:
    Scene(std::vector<ShaderProgram*> &shaders);
    void setSkybox(std::vector<std::string> faces,ShaderProgram* shader);
    void addObject(DrawableObject* obj);
    void drawScene();
    void transform(size_t index, TransformationComponent* transformation);
    Camera* getCamera();
    ~Scene();
};

#endif