#ifndef SKYBOX_CLASS_H
#define SKYBOX_CLASS_H

#include <SOIL/SOIL.h>

#include <glm/vec3.hpp>					// glm::vec3
#include <glm/vec4.hpp>					// glm::vec4
#include <glm/mat4x4.hpp>				// glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp>	

#include "VAO.h"
#include "VBO.h"
#include "ShaderProgram.h"
#include "models/skycube.h"

class Skybox
{
private:
    GLuint vao;
    VBO* vbo;
    ShaderProgram* shader;
    GLuint cubemapTexture;
public:
    Skybox(std::vector<std::string> faces, ShaderProgram* shader);
    void draw(glm::mat4 projection, glm::mat4 view);
    ~Skybox();
};


#endif