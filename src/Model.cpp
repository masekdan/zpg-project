#include "Model.h"

Model::Model(GLfloat* verticies, GLsizeiptr size, Shader* shader)
{

    vertexArray = new VAO();
	vertexArray->Bind();

	vertexBuffer = new VBO(verticies, size);

	vertexArray->LinkVBO(vertexBuffer, 0);
	vertexArray->Unbind();
	vertexArray->Unbind();

	this->shader = shader;
}

void Model::drawModel()
{
    this->shader->Activate();
    vertexArray->Bind();
    glDrawArrays(GL_POLYGON, 0, 4);
}