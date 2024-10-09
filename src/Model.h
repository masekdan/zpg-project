#ifndef MODEL_CLASS_H
#define MODEL_CLASS_H

#include "Shader.h"
#include "VAO.h"
#include "VBO.h"

class Model
{
private:
    Shader *shader;
    VBO *vertexBuffer;
    VAO *vertexArray;
    GLsizeiptr size;
public:
    Model(const GLfloat* verticies, GLsizeiptr size, Shader* shader);
    void drawModel();
};



#endif