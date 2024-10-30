#ifndef TRANSFORMATION_COMPOSITE_CLASS
#define TRANSFORMATION_COMPOSITE_CLASS

#include "TransformationComponent.h"

#include <vector>

class TransformationComposite : public TransformationComponent
{
private:
    std::vector<TransformationComponent*> transformations;
public:
    TransformationComposite();
    TransformationComposite(std::vector<TransformationComponent*> trans);
    void add(TransformationComponent* component) override;
    glm::mat4 getModelMatrix() override;
    ~TransformationComposite();
};


#endif