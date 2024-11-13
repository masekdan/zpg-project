#ifndef DRAWABLE_OBJECT_CLASS_H
#define DRAWABLE_OBJECT_CLASS_H

#include "ShaderProgram.h"
#include "VAO.h"
#include "VBO.h"
#include "Model.h"
#include "TransformationComponent.h"
#include "Light.h"

#include <glm/vec3.hpp>					// glm::vec3
#include <glm/vec4.hpp>					// glm::vec4
#include <glm/mat4x4.hpp>				// glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp>	
#include <vector>

class DrawableObject
{
private:
    ShaderProgram* shader;
    TransformationComponent* transformation;
    Model* model;
    Light* light;
    std::vector<Light*> lights;
public:
    DrawableObject(Model* model, ShaderProgram* shader, TransformationComponent* transformation, std::vector<Light*> lights);
    ~DrawableObject();
    void transform(TransformationComponent* transformation);
    void draw();
};

class DrawableObjectFactory
{
    public:
        DrawableObject* create(Model* model, ShaderProgram* shader, TransformationComponent* transformation, std::vector<Light*> lights);
};


#endif