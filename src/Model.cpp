#include "Model.h"

Model::Model(const GLfloat* verticies, GLsizeiptr size, Shader* shader)
{

    vertexArray = new VAO();
	vertexArray->Bind();
	this->size = size;
	vertexBuffer = new VBO(verticies, size);

	vertexArray->LinkVBO(vertexBuffer);
	vertexArray->Unbind();
	vertexArray->Unbind();

	this->shader = shader;
}

void Model::drawModel()
{
    this->shader->Activate();
    vertexArray->Bind();
    glDrawArrays(GL_TRIANGLES, 0, this->size / 6);
}