#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H


#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>					// glm::vec3
#include <glm/vec4.hpp>					// glm::vec4
#include <glm/mat4x4.hpp>				// glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp>	
#include <vector>

#include "Observer.h"

class ShaderProgram;

class Camera
{
private:
    std::vector<Observer*> shaders;
    glm::vec3 eye;
    glm::vec3 center;
    glm::vec3 up;

    glm::mat4 view;
    glm::mat4 projection;

    bool firstClick = true;
    float pitch = 0.0f;  //up-down alpha
    float yaw = -90.0f;  //left-right fi

    void notifyObservers();

public:
    Camera(glm::vec3 eye, glm::vec3 center, glm::vec3 up);
    void registerShader(Observer* shader);
    void removeShader(Observer* shader);
    void matrix(float FOV, float nearPlane, float farPlate);
    void inputs(GLFWwindow* window);
    ~Camera();
};



#endif