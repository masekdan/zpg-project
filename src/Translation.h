#ifndef TRANSLATION_CLASS_H
#define TRANSLATION_CLASS_H

#include <glm/vec3.hpp>					// glm::vec3
#include <glm/vec4.hpp>					// glm::vec4
#include <glm/mat4x4.hpp>				// glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp>

#include "TransformationComponent.h"


class Translation : public TransformationComponent
{
private:
    glm::vec3 position;
public:
    Translation(glm::vec3 pos);
    glm::mat4 getModelMatrix() override;
};




#endif