#include "Model.h"

Model::Model(const GLfloat* verticies, GLsizeiptr size)
{

    vertexArray = new VAO();
	vertexArray->Bind();
	this->size = size;
	vertexBuffer = new VBO(verticies, size);

	vertexArray->LinkVBO(vertexBuffer);
	vertexArray->Unbind();
	vertexArray->Unbind();

}

void Model::drawModel()
{
    vertexArray->Bind();
    glDrawArrays(GL_TRIANGLES, 0, this->size / 6);
}

Model::~Model()
{
	this->vertexArray->Delete();
	this->vertexBuffer->Delete();
}