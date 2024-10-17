#include "Camera.h"
#include "ShaderProgram.h"

Camera::Camera(glm::vec3 eye, glm::vec3 center, glm::vec3 up)
{
    this->eye = eye;
    this->center = center;
    this->up = up;
}

void Camera::registerShader(ShaderProgram* shader)
{
    this->shaders.push_back(shader);
}

void Camera::matrix(float FOV, float nearPlane, float farPlane)
{
    glm::mat4 view = glm::mat4(1.0);
    glm::mat4 projection = glm::mat4(1.0);

    view = glm::lookAt(this->eye,this->center,this->up);
    projection = glm::perspective(glm::radians(FOV),4.0f/3.0f,nearPlane,farPlane);

    for (auto* s : this->shaders)
    {
        s->SetUniform("view",view);
        s->SetUniform("projection",projection);
    }
}