#ifndef SCENE_CLASS_H
#define SCENE_CLASS_H

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
    void transform();
};

#endif