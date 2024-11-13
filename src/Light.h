#ifndef LIGHT_CLASS_H
#define LIGHT_CLASS_H

#include <glm/vec3.hpp>

class Light
{
private:
    glm::vec3 position;
    glm::vec3 attenuation;
public:
    Light(glm::vec3 pos, glm::vec3 attenuation);
    glm::vec3 getPosition();
    glm::vec3 getAttenuation();
    ~Light();
};



#endif