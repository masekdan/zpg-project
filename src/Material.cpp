#include "Material.h"

Material::Material(glm::vec3 ra, glm::vec3 rd, glm::vec3 rs) : ra(ra), rd(rd), rs(rs)
{

}

glm::vec3 Material::getRa() const
{
    return this->ra;
}

glm::vec3 Material::getRd() const
{
    return this->rd;
}

glm::vec3 Material::getRs() const
{
    return this->rs;
}