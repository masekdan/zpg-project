#include "ShaderProgram.h"
#include "Camera.h"


void ShaderProgram::update()
{
    this->Activate();
    this->SetUniform("projection",this->camera->getProjection());
    this->SetUniform("view",this->camera->getView());
    this->SetUniform("eye",this->camera->getEye());
}

ShaderProgram::ShaderProgram(const char *vertexFile, const char *fragmentFile)
{
    
    ID = this->loader.loadShader(vertexFile,fragmentFile);

    GLint status;
    glGetProgramiv(ID, GL_LINK_STATUS, &status);
    if (status == GL_FALSE)
    {
        GLchar strInfoLog[512];
        glGetProgramInfoLog(ID, 512, nullptr, strInfoLog);
        fprintf(stderr, " Linker ␣ failure :\n %s \n ", strInfoLog);
        exit(-2);
    }
}

void ShaderProgram::SetUniform(char* name, glm::mat4 matrix)
{
    int uniformLocation = glGetUniformLocation(this->ID,name);
    glUniformMatrix4fv(uniformLocation,1,GL_FALSE,glm::value_ptr(matrix));
}

void ShaderProgram::SetUniform(char* name, glm::vec3 matrix)
{
    int uniformLocation = glGetUniformLocation(this->ID,name);
    glUniform3fv(uniformLocation,1,glm::value_ptr(matrix));
}


void ShaderProgram::registerSubject(Subject* subject)
{
    this->camera = static_cast<Camera*>(subject);
}

void ShaderProgram::Activate()
{
    glUseProgram(ID);
}

void ShaderProgram::Delete()
{
    this->loader.deleteShader();
    glDeleteProgram(ID);
}

ShaderProgram::~ShaderProgram()
{
    this->Delete();
}