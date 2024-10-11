#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>

#include <GL/glew.h>

std::string get_file_contents(const char* filename);

class Shader
{
private:
    GLuint ID;
public:
    
    Shader(const char* vertexFile, const char* fragmentFile);

    void Activate();
    void Delete();
    int GetLocation(char * name);
    
};



#endif