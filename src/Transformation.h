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
    glm::mat4 model;
public:
    Transformation();
    void rotate(float angle);
    void scale(float scale);
    void translate(float direction);
    glm::mat4 getModelMatrix();
};




#endif