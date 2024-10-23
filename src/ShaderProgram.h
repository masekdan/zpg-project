#ifndef SHADER_PROGRAM_CLASS_H
#define SHADER_PROGRAM_CLASS_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>

#include <GL/glew.h>
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera;

std::string get_file_contents(const char* filename);

class ShaderProgram
{
private:
    GLuint ID;
    Camera *camera;
public:
    
    ShaderProgram(const char* vertexFile, const char* fragmentFile);

    void Activate();
    void Delete();
    void SetUniform(char * name,glm::mat4 matrix);
    void SetUniform(char * name,glm::mat3 matrix);
    
};



#endif