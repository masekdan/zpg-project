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

class ShaderProgram;

class Camera
{
private:
    std::vector<ShaderProgram*> shaders;
    glm::vec3 eye;
    glm::vec3 center;
    glm::vec3 up;

    bool firstClick = true;
    float pitch = 0.0f;  //up-down
    float yaw = -90.0f;  //left-right

public:
    Camera(glm::vec3 eye, glm::vec3 center, glm::vec3 up);
    void registerShader(ShaderProgram* shader);
    void removeShader(ShaderProgram* shader);
    void matrix(float FOV, float nearPlane, float farPlate);
    void inputs(GLFWwindow* window);
    ~Camera();
};



#endif