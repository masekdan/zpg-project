#include "VAO.h"

VAO::VAO()
{
	glGenVertexArrays(1, &ID);	  // generate the VAO
}

void VAO::LinkVBO(VBO VBO, GLuint layout)
{
    VBO.Bind();
    glVertexAttribPointer(layout, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(layout); // enable vertex attributes
    VBO.Unbind();
}

void VAO::Bind()
{
    glBindVertexArray(ID);
}

void VAO::Unbind()
{
    glBindVertexArray(0);
}

void VAO::Delete()
{
    glDeleteVertexArrays(1, &ID);
}