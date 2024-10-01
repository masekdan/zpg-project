#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include <GL/glew.h>

class VBO
{
    private:
        GLuint ID;
    public:
        
        VBO(GLfloat* verticies, GLsizeiptr size);

        void Bind();
        void Unbind();
        void Delete();
};

#endif