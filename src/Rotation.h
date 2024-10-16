#ifndef ROTATION_CLASS_H
#define ROTATION_CLASS_H

#include "TransformationComponent.h"
#include <glm/gtc/matrix_transform.hpp>

class Rotation : public TransformationComponent
{
private:
    glm::vec3 rotation;
public:
    Rotation(glm::vec3 rot);
    glm::mat4 getModelMatrix() override;
};


#endif