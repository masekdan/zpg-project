#include "VAO.h"

VAO::VAO()
{
    glGenVertexArrays(1, &ID); // generate the VAO
}

void VAO::LinkVBO(VBO *VBO, bool hasTexture)
{
    VBO->Bind();
    // glVertexAttribPointer(layout, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    // glEnableVertexAttribArray(layout); // enable vertex attributes
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    if (hasTexture == false)
    {
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid *)0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid *)(3 * sizeof(float)));
    }
    else if (hasTexture == true)
    {
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid *)0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid *)(3 * sizeof(float)));
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid *)(sizeof(float) * 6));
    }
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