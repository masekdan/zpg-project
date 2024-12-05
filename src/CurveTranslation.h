#ifndef CURVETRANSLATION_CLASS_H
#define CURVETRANSLATION_CLASS_H

#include "TransformationComponent.h"
#include <glm/gtc/matrix_transform.hpp>

class CurveTranslation : public TransformationComponent
{
private:
    float t;
    float delta;
    glm::mat4x3 points;
    glm::mat4 coeff;
    float move();
public:
    CurveTranslation(glm::mat4x3 points, float parameter, float speed);
    glm::mat4 getModelMatrix() override;
};


#endif