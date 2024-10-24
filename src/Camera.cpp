#include "Camera.h"
#include "ShaderProgram.h"

Camera::Camera(glm::vec3 eye, glm::vec3 center, glm::vec3 up)
{
    this->eye = eye;
    this->center = center;
    this->up = up;

    this->view = glm::mat4(1.0);
    this->projection = glm::mat4(1.0);
}

void Camera::notifyObservers()
{
    for (auto* s : this->shaders)
    {
        s->update(this->view,this->projection,this->eye);
    }
    
}

void Camera::registerShader(Observer* shader)
{
    this->shaders.push_back(shader);
}

void Camera::matrix(float FOV, float nearPlane, float farPlane)
{

    this->view = glm::lookAt(this->eye,this->center,this->up);
    this->projection = glm::perspective(glm::radians(FOV),4.0f/3.0f,nearPlane,farPlane);

    this->notifyObservers();
}

void Camera::inputs(GLFWwindow* window)
{
    glm::vec3 forward = glm::normalize(center - eye);
    glm::vec3 right = glm::normalize(glm::cross(forward,up));
    glm::vec3 vertical = glm::normalize(up);

    float speed = 0.1f;
    float sens = 0.1f;

    if (glfwGetKey(window,GLFW_KEY_W)==GLFW_PRESS)
    {
        this->eye += speed * forward;
        this->center += speed * forward;
    }
    if (glfwGetKey(window,GLFW_KEY_S)==GLFW_PRESS)
    {
        this->eye -= speed * forward;
        this->center -= speed * forward;
    }
    if (glfwGetKey(window,GLFW_KEY_D)==GLFW_PRESS)
    {
        this->eye += speed * right;
        this->center += speed * right;
    }
    if (glfwGetKey(window,GLFW_KEY_A)==GLFW_PRESS)
    {
        this->eye -= speed * right;
        this->center -= speed * right;
    }
    if (glfwGetKey(window,GLFW_KEY_SPACE)==GLFW_PRESS)
    {
        this->eye += speed * vertical;
        this->center += speed * vertical;
    }
    if (glfwGetKey(window,GLFW_KEY_LEFT_SHIFT)==GLFW_PRESS)
    {
        this->eye -= speed * vertical;
        this->center -= speed * vertical;
    }

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
    {
        glfwSetInputMode(window,GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

        if (firstClick)
        {
            glfwSetCursorPos(window, (800/2),(600/2));
            firstClick = false;
        }

        double mouseX;
        double mouseY;

        glfwGetCursorPos(window, &mouseX, &mouseY);

        float xoffset = (mouseX - 800 / 2 )*sens;
        float yoffset = (600/2 - mouseY)*sens;

        yaw += xoffset;
        pitch += yoffset;

        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;

        glm::vec3 direction;
        direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        direction.y = sin(glm::radians(pitch));
        direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

        this->center = glm::normalize(direction) + eye;

        glfwSetCursorPos(window,800/2,600/2);
    }

    else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        firstClick = true;
    }
}