#ifndef DYNAMICROTATION_CLASS_H
#define DYNAMICROTATION_CLASS_H

#include "TransformationComponent.h"
#include <glm/gtc/matrix_transform.hpp>

class DynamicRotation : public TransformationComponent
{
private:
    glm::vec3 rotation;
    float speed;
    float rotate(float angle);
public:
    DynamicRotation(glm::vec3 rot, float speed);
    glm::mat4 getModelMatrix() override;
};


#endif