#ifndef MODEL_CLASS_H
#define MODEL_CLASS_H

#include "ShaderProgram.h"
#include "VAO.h"
#include "VBO.h"

#include <SOIL/SOIL.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class Model
{
private:
    VBO *vertexBuffer;
    VAO *vertexArray;
    GLsizeiptr size;
    bool hasTexture;
    GLuint img;
public:
    Model(const GLfloat* verticies, GLsizeiptr size, bool hasTexture);
    Model(char* path);
    ~Model();
    void drawModel();
    void setTexture(char* path);
    bool hasTextureMet();
};



#endif