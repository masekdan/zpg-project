#ifndef POINTLIGHT_CLASS_H
#define POINTLIGHT_CLASS_H

#include "Light.h"
#include <glm/vec3.hpp>

class PointLight : public Light
{
private:
    glm::vec3 position;
    glm::vec3 attenuation;
public:
    
    PointLight(glm::vec3 position,glm::vec3 attenuation);
    int getType() override;
    glm::vec3 getPosition();
    glm::vec3 getAttenuation();
};




#endif