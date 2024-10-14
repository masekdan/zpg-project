#ifndef TRANSFORMATION_COMPOSITE_CLASS
#define TRANSFORMATION_COMPOSITE_CLASS

#include "TransformationComponent.h"

#include <vector>

class TransformationComposite : public TransformationComponent
{
private:
    std::vector<TransformationComponent*> transformations;
public:
    void add(TransformationComponent* component) override;
    glm::mat4 getModelMatrix() override;
};


#endif