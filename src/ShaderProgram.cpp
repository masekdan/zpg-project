#include "ShaderProgram.h"
#include "Camera.h"


void ShaderProgram::update(const glm::mat4 view,const glm::mat4 projection, glm::vec3 eye)
{
    this->Activate();
    this->SetUniform("projection",projection);
    this->SetUniform("view",view);
    this->SetUniform("eye",eye);
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

void ShaderProgram::Activate()
{
    glUseProgram(ID);
}

void ShaderProgram::Delete()
{
    glDeleteProgram(ID);
}