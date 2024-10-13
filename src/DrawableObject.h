#ifndef DRAWABLE_OBJECT_CLASS_H
#define DRAWABLE_OBJECT_CLASS_H

#include "Shader.h"
#include "VAO.h"
#include "VBO.h"
#include "Model.h"
#include "Transformation.h"

#include <glm/vec3.hpp>					// glm::vec3
#include <glm/vec4.hpp>					// glm::vec4
#include <glm/mat4x4.hpp>				// glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp>	

class DrawableObject
{
private:
    Shader* shader;
    Transformation* transformation;
    Model* model;
public:
    DrawableObject(Model* model, Shader* shader, Transformation* transformation);
    void draw();
};

class DrawableObjectFactory
{
    public:
        DrawableObject* create(Model* model, Shader* shader, Transformation* transformation);
};


#endif