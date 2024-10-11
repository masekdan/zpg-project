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

void Model::drawModel(float angle)
{
    this->shader->Activate();

	glm::mat4 model = glm::mat4(1.0f);

	model = glm::rotate(model,glm::radians(angle),glm::vec3(0.0f,1.0f,0.0f));
	model = glm::translate(model,glm::vec3(0.0f,-0.5f,0.0f));
	model = glm::scale(model,glm::vec3(0.5f));

	int modelLoc = this->shader->GetLocation("model");
	glUniformMatrix4fv(modelLoc,1,GL_FALSE,glm::value_ptr(model));


    vertexArray->Bind();
    glDrawArrays(GL_TRIANGLES, 0, this->size / 6);
}