#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include <GL/glew.h>
#include "VBO.h"

class VAO
{

    private:
        GLuint ID;
    public:
        
        VAO();

        void LinkVBO(VBO* VBO,bool hasTexture);
        void Bind();
        void Unbind();
        void Delete();
};

#endif