#ifndef DIRECTIONLIGHT_CLASS_H
#define DIRECTIONLIGHT_CLASS_H

#include "Light.h"
#include <glm/vec3.hpp>

class DirectionLight : public Light
{
private:
    glm::vec3 direction;
public:
    DirectionLight(glm::vec3 direction);
    int getType() override;
    glm::vec3 getDirection();
};



#endif