#ifndef MODEL_CLASS_H
#define MODEL_CLASS_H

#include "ShaderProgram.h"
#include "VAO.h"
#include "VBO.h"

class Model
{
private:
    VBO *vertexBuffer;
    VAO *vertexArray;
    GLsizeiptr size;
public:
    Model(const GLfloat* verticies, GLsizeiptr size);
    void drawModel();
};



#endif