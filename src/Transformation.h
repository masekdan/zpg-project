#ifndef TRANSFORMATION_CLASS_H
#define TRANSFORMATION_CLASS_H

#include <glm/vec3.hpp>					// glm::vec3
#include <glm/vec4.hpp>					// glm::vec4
#include <glm/mat4x4.hpp>				// glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp>


class Transformation
{
private:
    glm::vec3 position;
    glm::vec3 rotation;
    float scale;
public:
    Transformation(glm::vec3 pos, glm::vec3 rot, float sc);
    glm::mat4 getModelMatrix();
};




#endif