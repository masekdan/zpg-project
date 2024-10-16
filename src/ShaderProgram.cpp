#include "ShaderProgram.h"

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
        GLint info;
        glGetProgramiv(ID, GL_INFO_LOG_LENGTH, &info);
        GLchar *strInfoLog = new GLchar[info];
        glGetProgramInfoLog(ID, info, &info, strInfoLog);
        fprintf(stderr, " Linker ␣ failure : ␣ % s \ n ", strInfoLog);
        delete[] strInfoLog;
        exit(-2);
    }
}

int ShaderProgram::GetLocation(char * name)
{
    return glGetUniformLocation(this->ID,name);
}

void ShaderProgram::Activate()
{
    glUseProgram(ID);
}

void ShaderProgram::Delete()
{
    glDeleteProgram(ID);
}