#ifndef SPOTLIGHT_CLASS_H
#define SPOTLIGHT_CLASS_H

#include "Light.h"
#include <glm/vec3.hpp>

class SpotLight : public Light
{
private:
    glm::vec3 position;
    glm::vec3 direction;
    float theta;
public:
    SpotLight(/* args */);
    ~SpotLight();
};



#endif