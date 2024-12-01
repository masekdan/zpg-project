#include "Model.h"

Model::Model(const GLfloat* verticies, GLsizeiptr size, bool hasTexture)
{
	this->hasTexture = hasTexture;
    vertexArray = new VAO();
	vertexArray->Bind();
	this->size = size;
	vertexBuffer = new VBO(verticies, size);

	vertexArray->LinkVBO(vertexBuffer,this->hasTexture);
	vertexArray->Unbind();
	vertexArray->Unbind();

	

}

bool Model::hasTextureMet()
{
	return this->hasTexture;
}


void Model::setTexture(char* path)
{
	this->img = SOIL_load_OGL_texture(path,SOIL_LOAD_RGBA, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);

	this->hasTexture = true;

	glBindTexture(GL_TEXTURE_2D, this->img);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Model::drawModel()
{
	if (hasTexture) {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, this->img);
    }

    vertexArray->Bind();
    glDrawArrays(GL_TRIANGLES, 0, this->size / 8);
}

Model::~Model()
{
	this->vertexArray->Delete();
	this->vertexBuffer->Delete();
}