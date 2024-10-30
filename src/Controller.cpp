#include "Controller.h"

Controller::Controller(GLFWwindow* window)
{
    this->window = window;
}

void Controller::HandleInput()
{
    if (glfwGetKey(window,GLFW_KEY_W)==GLFW_PRESS)
    {

    }
    if (glfwGetKey(window,GLFW_KEY_S)==GLFW_PRESS)
    {
        
    }
    if (glfwGetKey(window,GLFW_KEY_A)==GLFW_PRESS)
    {
        
    }
    if (glfwGetKey(window,GLFW_KEY_D)==GLFW_PRESS)
    {
        
    }
    if (glfwGetKey(window,GLFW_KEY_LEFT_SHIFT)==GLFW_PRESS)
    {
        
    }
    if (glfwGetKey(window,GLFW_KEY_SPACE)==GLFW_PRESS)
    {
        
    }

}