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

#include "Observer.h"

class Camera;

std::string get_file_contents(const char* filename);

class ShaderProgram : public Observer
{
private:
    GLuint ID;
    Camera *camera;
public:
    
    ShaderProgram(const char* vertexFile, const char* fragmentFile);

    void Activate();
    void Delete();
    void update(const glm::mat4 view,const glm::mat4 projection) override;
    void SetUniform(char * name,glm::mat4 matrix);
    void SetUniform(char * name,glm::mat3 matrix);
    
};



#endif