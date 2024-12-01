#include "ShaderProgram.h"
#include "Camera.h"

void ShaderProgram::update()
{
    this->Activate();
    this->SetUniform("projection", this->camera->getProjection());
    this->SetUniform("view", this->camera->getView());
    this->SetUniform("eye", this->camera->getEye());
    // this->Deactivate();
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
        // std::cout << "This uniform \"" << name << "\" does not exist." << std::endl;
    }
    else
    {
        glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(matrix));
    }
}

void ShaderProgram::SetUniform(char* name, int var)
{
    int uniformLocation = glGetUniformLocation(this->ID, name);
    if (uniformLocation == -1)
    {
        // std::cout << "This uniform \"" << name << "\" does not exist." << std::endl;
    }
    else
    {
        glUniform1i(uniformLocation,var);
    }
}

void ShaderProgram::SetUniform(char *name, glm::vec3 matrix)
{
    int uniformLocation = glGetUniformLocation(this->ID, name);
    if (uniformLocation == -1)
    {
        // std::cout << "This uniform \"" << name << "\" does not exist." << std::endl;
    }
    else
    {
        glUniform3fv(uniformLocation, 1, glm::value_ptr(matrix));
    }
}

void ShaderProgram::SetLights(std::vector<Light *> lights)
{
    int size = lights.size();
    int lightSizeLocation = glGetUniformLocation(this->ID, "lightCount");
    glUniform1i(lightSizeLocation, size);
    for (int i = 0; i < size; i++)
    {
        if (lights[i]->getType() == 1)
        {
            PointLight* pl = static_cast<PointLight*>(lights[i]);
            std::string loc;
            std::stringstream ss;
            ss << "lights[" << i << "].position";
            loc = ss.str();
            int lightPosLocation = glGetUniformLocation(this->ID, loc.c_str());
            glUniform3fv(lightPosLocation, 1, glm::value_ptr(pl->getPosition()));
            ss = std::stringstream();
            ss << "lights[" << i << "].attenuation";
            loc = ss.str();
            int lightAttLocation = glGetUniformLocation(this->ID, loc.c_str());
            glUniform3fv(lightAttLocation, 1, glm::value_ptr(pl->getAttenuation()));
            ss = std::stringstream();
            ss << "lights[" << i << "].type";
            loc = ss.str();
            int lightTypeLoc = glGetUniformLocation(this->ID, loc.c_str());
            glUniform1i(lightTypeLoc, pl->getType());
        }
        else if (lights[i]->getType() == 2)
        {
            DirectionLight* dl = static_cast<DirectionLight*>(lights[i]);
            std::string loc;
            std::stringstream ss;
            ss << "lights[" << i << "].direction";
            loc = ss.str();
            int lightDirLoc = glGetUniformLocation(this->ID,loc.c_str());
            glUniform3fv(lightDirLoc,1,glm::value_ptr(dl->getDirection()));
            ss = std::stringstream();
            ss << "lights[" << i << "].type";
            loc = ss.str();
            int lightTypeLoc = glGetUniformLocation(this->ID, loc.c_str());
            glUniform1i(lightTypeLoc, dl->getType());
        }

        else if (lights[i]->getType() == 3)
        {
            SpotLight* sl = static_cast<SpotLight*>(lights[i]);
            std::string loc;
            std::stringstream ss;
            ss << "lights[" << i << "].direction";
            loc = ss.str();
            int lightDirLoc = glGetUniformLocation(this->ID,loc.c_str());
            glUniform3fv(lightDirLoc,1,glm::value_ptr(sl->getDirection()));
            ss = std::stringstream();
            ss << "lights[" << i << "].type";
            loc = ss.str();
            int lightTypeLoc = glGetUniformLocation(this->ID, loc.c_str());
            glUniform1i(lightTypeLoc, sl->getType());
            ss = std::stringstream();
            ss << "lights[" << i << "].position";
            loc = ss.str();
            int lightPosLocation = glGetUniformLocation(this->ID, loc.c_str());
            glUniform3fv(lightPosLocation, 1, glm::value_ptr(sl->getPosition()));
            ss = std::stringstream();
            ss << "lights[" << i << "].attenuation";
            loc = ss.str();
            int lightAttLocation = glGetUniformLocation(this->ID, loc.c_str());
            glUniform3fv(lightAttLocation, 1, glm::value_ptr(sl->getAttenuation()));
            ss = std::stringstream();
            ss << "lights[" << i << "].alpha";
            loc = ss.str();
            int angleLoc = glGetUniformLocation(this->ID, loc.c_str());
            glUniform1f(angleLoc,sl->getAngle());
        }
    }
}

void ShaderProgram::SetMaterial(Material *material)
{

    int raLoc = glGetUniformLocation(this->ID, "material.ra");
    int rdLoc = glGetUniformLocation(this->ID, "material.rd");
    int rsLoc = glGetUniformLocation(this->ID, "material.rs");

    glUniform3fv(raLoc, 1, glm::value_ptr(material->getRa()));

    glUniform3fv(rdLoc, 1, glm::value_ptr(material->getRd()));

    glUniform3fv(rsLoc, 1, glm::value_ptr(material->getRs()));
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