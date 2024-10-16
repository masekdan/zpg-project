#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H

#include <glm/vec3.hpp>					// glm::vec3
#include <glm/vec4.hpp>					// glm::vec4
#include <glm/mat4x4.hpp>				// glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp>	


class Camera
{
private:
    /* data */
public:
    Camera(glm::vec3 eye, glm::vec3 center);
    ~Camera();
};



#endif