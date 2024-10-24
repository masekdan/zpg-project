#include "TransformationComposite.h"

TransformationComposite::TransformationComposite()
{
    
}

TransformationComposite::TransformationComposite(std::vector<TransformationComponent*> trans)
{
    this->transformations = trans;
}

void TransformationComposite::add(TransformationComponent* component)
{
    this->transformations.push_back(component);
}

glm::mat4 TransformationComposite::getModelMatrix()
{
    glm::mat4 model = glm::mat4(1.0f);

    for (auto* t : this->transformations)
    {
        model *= t->getModelMatrix();
    }
    return model;
}