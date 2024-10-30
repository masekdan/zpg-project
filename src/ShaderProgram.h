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
#include "ShaderLoader.h"

class Camera;

class ShaderProgram : public Observer
{
private:
    GLuint ID;
    Camera *camera;
    ShaderLoader loader;
public:
    
    ShaderProgram(const char* vertexFile, const char* fragmentFile);
    ~ShaderProgram();

    void Activate();
    void Delete();
    void SetCamera(Camera *cam);
    void update(const glm::mat4 view,const glm::mat4 projection, glm::vec3 eye) override;
    void SetUniform(char * name,glm::mat4 matrix);
    void SetUniform(char * name,glm::vec3 matrix);
    
};



#endif