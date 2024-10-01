#ifndef MODEL_CLASS_H
#define MODEL_CLASS_H

#include "Shader.h"
#include "VAO.h"
#include "VBO.h"

class Model
{
private:
    Shader *shader;
    VBO *buffer;
    VAO *array;
public:
    Model(GLfloat* verticies, GLsizeiptr size, Shader* shader);
    void drawModel();
};



#endif