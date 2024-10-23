#ifndef OBSERVER_CLASS_H
#define OBSERVER_CLASS_H

#include <glm/mat4x4.hpp>

class Observer
{
private:
    
public:
    virtual void update(const glm::mat4 view,const glm::mat4 projection) = 0;
};



#endif