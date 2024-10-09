#ifndef APPLICATION_CLASS_H
#define APPLICATION_CLASS_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/vec3.hpp>					// glm::vec3
#include <glm/vec4.hpp>					// glm::vec4
#include <glm/mat4x4.hpp>				// glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp>			// glm::value_ptr

// Include the standard C++ headers
#include <stdlib.h>
#include <stdio.h>
#include <vector>

#include "Shader.h"
#include "VBO.h"
#include "VAO.h"
#include "Model.h"
#include "models/gift.h"
#include "models/suzi_flat.h"
#include "models/tree.h"

class Application
{
private:
    GLFWwindow *window;
    std::vector<Shader*> shaders; 
    std::vector<Model*> models;
public:
    Application();
    void initialization();
    void createShaders();
    void createModels();
    void run();
};



#endif