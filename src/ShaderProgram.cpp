#include "ShaderProgram.h"
#include "Camera.h"

void ShaderProgram::update()
{
    this->Activate();
    this->SetUniform("projection", this->camera->getProjection());
    this->SetUniform("view", this->camera->getView());
    this->SetUniform("eye", this->camera->getEye());
    //this->Deactivate();
    glUseProgram(0);
}

ShaderProgram::ShaderProgram(const char *vertexFile, const char *fragmentFile)
{

    ID = this->loader.loadShader(vertexFile, fragmentFile);

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

void ShaderProgram::SetUniform(char *name, glm::mat4 matrix)
{
    int uniformLocation = glGetUniformLocation(this->ID, name);
    if (uniformLocation == -1)
    {
        //std::cout << "This uniform \"" << name << "\" does not exist." << std::endl;
    }
    else
    {
        glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(matrix));
    }
}

void ShaderProgram::SetUniform(char *name, glm::vec3 matrix)
{
    int uniformLocation = glGetUniformLocation(this->ID, name);
    if (uniformLocation == -1)
    {
        //std::cout << "This uniform \"" << name << "\" does not exist." << std::endl;
    }
    else
    {
        glUniform3fv(uniformLocation, 1, glm::value_ptr(matrix));
    }
}

void ShaderProgram::SetLights(std::vector<Light*> lights)
{
    int size = lights.size();
    int lightSizeLocation = glGetUniformLocation(this->ID,"lightCount");
    glUniform1i(lightSizeLocation,size);
    for (int i = 0; i<size;i++)
    {
        std::string loc;
        std::stringstream ss;
        ss << "lights[" << i << "].position";
        loc = ss.str();
        int lightPosLocation = glGetUniformLocation(this->ID,loc.c_str());
        glUniform3fv(lightPosLocation,1,glm::value_ptr(lights[i]->getPosition()));
        ss = std::stringstream();
        ss << "lights[" << i <<  "].attenuation";
        loc = ss.str();
        int lightAttLocation = glGetUniformLocation(this->ID,loc.c_str());
        glUniform3fv(lightAttLocation,1,glm::value_ptr(lights[i]->getAttenuation()));
    }
}

void ShaderProgram::registerSubject(Subject *subject)
{
    this->camera = static_cast<Camera *>(subject);
}

void ShaderProgram::Activate()
{
    glUseProgram(ID);
}

void ShaderProgram::Deactivate()
{
    glUseProgram(0);
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