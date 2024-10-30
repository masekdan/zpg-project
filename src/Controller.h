#ifndef CONTROLLER_CLASS
#define CONTROLLER_CLASS

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Controller
{
private:
    GLFWwindow* window;
public:
    Controller(GLFWwindow* window);
    void HandleInput();
    ~Controller();
};

#endif