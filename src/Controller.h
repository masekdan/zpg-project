#ifndef CONTROLLER_CLASS
#define CONTROLLER_CLASS

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Camera.h"

class Controller
{
private:
    GLFWwindow* window;
    Camera* cam;
public:
    Controller(GLFWwindow* window);
    void HandleInput();
    void RegisterCamera(Camera* camera);
    ~Controller();
};

#endif