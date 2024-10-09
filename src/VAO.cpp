#include "VAO.h"

VAO::VAO()
{
	glGenVertexArrays(1, &ID);	  // generate the VAO
}

void VAO::LinkVBO(VBO* VBO)
{
    VBO->Bind();
    //glVertexAttribPointer(layout, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    //glEnableVertexAttribArray(layout); // enable vertex attributes
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid*)(3 * sizeof(float)));
    VBO->Unbind();
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