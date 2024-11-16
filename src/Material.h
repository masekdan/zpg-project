#ifndef MATERIAL_CLASS_H
#define MATERIAL_CLASS_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>	
#include <glm/vec4.hpp>

class Material
{
private:
    glm::vec3 ra;
    glm::vec3 rd;
    glm::vec3 rs;
public:
    Material(glm::vec3 ra, glm::vec3 rd, glm::vec3 rs);
    glm::vec3 getRa() const;
    glm::vec3 getRd() const;
    glm::vec3 getRs() const;
    ~Material();
};


#endif