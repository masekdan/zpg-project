#include "Model.h"

Model::Model(GLfloat* verticies, GLsizeiptr size, Shader* shader)
{

    array = new VAO();
	array->Bind();

	buffer = new VBO(verticies, size);

	array->LinkVBO(buffer, 0);
	array->Unbind();
	array->Unbind();
}

void Model::drawModel()
{
    //shader->Activate();
    array->Bind();
    glDrawArrays(GL_POLYGON, 0, 4);
}