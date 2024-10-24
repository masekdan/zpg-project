#include "ShaderProgram.h"
#include "Camera.h"

std::string get_file_contents(const char *filename)
{
    std::ifstream in(filename, std::ios::binary);
    if (in)
    {
        std::string contents;
        in.seekg(0, std::ios::end);
        contents.resize(in.tellg());
        in.seekg(0, std::ios::beg);
        in.read(&contents[0], contents.size());
        in.close();
        return (contents);
    }
    throw(errno);
}

void ShaderProgram::update(const glm::mat4 view,const glm::mat4 projection, glm::vec3 eye)
{
    this->Activate();
    this->SetUniform("projection",projection);
    this->SetUniform("view",view);
    this->SetUniform("eye",eye);
}

ShaderProgram::ShaderProgram(const char *vertexFile, const char *fragmentFile)
{
    std::string vertexCode = get_file_contents(vertexFile);
    std::string fragmentCode = get_file_contents(fragmentFile);

    const char *vertexSource = vertexCode.c_str();
    const char *fragmentSource = fragmentCode.c_str();

    // create and compile shaders
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glCompileShader(vertexShader);
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);
    ID = glCreateProgram();
    glAttachShader(ID, fragmentShader);
    glAttachShader(ID, vertexShader);
    glLinkProgram(ID);

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