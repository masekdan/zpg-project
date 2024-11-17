#ifndef SPOTLIGHT_CLASS_H
#define SPOTLIGHT_CLASS_H

#include "Light.h"
#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>	

class SpotLight : public Light
{
protected:
    glm::vec3 position;
    glm::vec3 direction;
    glm::vec3 attenuation;
    float angle;
public:
    SpotLight(glm::vec3 position, glm::vec3 direction, float angle,glm::vec3 attenuation);
    int getType() override;
    glm::vec3 getPosition();
    glm::vec3 getDirection();
    glm::vec3 getAttenuation();
    float getAngle();
};



#endif