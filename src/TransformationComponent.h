#ifndef TRANSFORMATION_COMPONENT_CLASS
#define TRANSFORMATION_COMPONENT_CLASS

#include <glm/glm.hpp>

class TransformationComponent
{

public:
    virtual glm::mat4 getModelMatrix() = 0;
    virtual void add(TransformationComponent* component) {}
    //virtual ~TransformationComponent();
};



#endif