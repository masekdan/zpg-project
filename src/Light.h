#ifndef LIGHT_CLASS_H
#define LIGHT_CLASS_H

#include <glm/vec3.hpp>

class Light
{
private:
    glm::vec3 position;
public:
    Light(glm::vec3 pos);
    ~Light();
};



#endif