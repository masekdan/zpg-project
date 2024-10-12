#ifndef MODEL_CLASS_H
#define MODEL_CLASS_H

#include "Shader.h"
#include "VAO.h"
#include "VBO.h"
#include "Transformation.h"

#include <glm/vec3.hpp>					// glm::vec3
#include <glm/vec4.hpp>					// glm::vec4
#include <glm/mat4x4.hpp>				// glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp>	

class Model
{
private:
    Shader *shader;
    VBO *vertexBuffer;
    VAO *vertexArray;
    Transformation *trans;
    GLsizeiptr size;
public:
    Model(const GLfloat* verticies, GLsizeiptr size, Shader* shader);
    void drawModel(float angle);
};



#endif