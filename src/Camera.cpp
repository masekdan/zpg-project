#include "Camera.h"
#include "ShaderProgram.h"


Camera* Camera::instance = nullptr;
Camera::Camera(glm::vec3 eye, glm::vec3 center, glm::vec3 up)
{
    this->eye = eye;
    this->center = center;
    this->up = up;

    this->view = glm::mat4(1.0);
    this->projection = glm::mat4(1.0);

    this->width = 800;
    this->height = 600;
}

Camera* Camera::getInstance(glm::vec3 eye, glm::vec3 center, glm::vec3 up)
{
    if (!instance)
    {
        instance = new Camera(eye, center, up);
    }
    return instance;
}

void Camera::registerShader(Observer* shader)
{
    this->shaders.push_back(shader);
}

void Camera::matrix(float FOV, float nearPlane, float farPlane)
{

    this->view = glm::lookAt(this->eye,this->center,this->up);

    float aratio;
    if (this->height!=0)
    {
        aratio = this->width/this->height;
    }
    std::cout << this->eye.x << " " << this->eye.y << " " << this->eye.z << std::endl;
    this->projection = glm::perspective(glm::radians(FOV),aratio,nearPlane,farPlane);

    this->notifyObservers();
}

glm::mat4 Camera::getProjection()
{
    return this->projection;
}

glm::mat4 Camera::getView()
{
    return this->view;
}

glm::vec3 Camera::getEye()
{
    return this->eye;
}

glm::vec3 Camera::getDirection()
{
    return glm::normalize(this->center - this->eye);
}

void Camera::resizeWindow(GLFWwindow* window, int width, int height)
{
    this->width = width;
    this->height = height;
    glViewport(0,0,width,height);
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
            glfwSetCursorPos(window, (this->width/2),(this->height/2));
            firstClick = false;
        }

        double mouseX;
        double mouseY;

        glfwGetCursorPos(window, &mouseX, &mouseY);

        float xoffset = (mouseX - this->width / 2 )*sens;
        float yoffset = (this->height/2 - mouseY)*sens;

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

        glfwSetCursorPos(window,this->width/2,this->height/2);
    }

    else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        firstClick = true;
    }

    glfwSetFramebufferSizeCallback(window, [](GLFWwindow *window, int width, int height) {
    Camera::instance->resizeWindow(window,width,height);
});
}