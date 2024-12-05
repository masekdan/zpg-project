#include "CurveTranslation.h"

CurveTranslation::CurveTranslation(glm::mat4x3 points, float parameter, float speed)
{
    this->points = points;
    this->t = parameter;
    this->delta = speed;

    this->coeff = glm::mat4(glm::vec4(-1.0, 3.0, -3.0, 1.0),
                            glm::vec4(3.0, -6.0, 3.0, 0),
                            glm::vec4(-3.0, 3.0, 0, 0),
                            glm::vec4(1, 0, 0, 0));
}

float CurveTranslation::move()
{
    if (t >= 1.0f || t <= 0.0f) delta *= -1;
        t += delta;
    return t;
}

glm::mat4 CurveTranslation::getModelMatrix()
{
    this->t = move();
    glm::vec4 parameters = glm::vec4(t * t * t, t * t, t, 1.0f);
    glm::vec3 p = parameters * this->coeff * glm::transpose(this->points);

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, p);
    return model;
}