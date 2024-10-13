#ifndef APPLICATION_SCENE_H
#define APPLICATION_SCENE_H

#include "DrawableObject.h"
#include <vector>

class Scene
{
private:
    std::vector<DrawableObject*> objects;
public:
    Scene();
    void addObject(DrawableObject* obj);
    void drawScene();
};

#endif