#ifndef SCALE_CLASS_H
#define SCALE_CLASS_H

#include "TransformationComponent.h"
#include <glm/gtc/matrix_transform.hpp>

class Scale : public TransformationComponent
{
private:
    glm::vec3 scale;
public:
    Scale(glm::vec3 scale);
    glm::mat4 getModelMatrix() override;
};


#endif