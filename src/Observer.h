#ifndef OBSERVER_CLASS_H
#define OBSERVER_CLASS_H

#include "Subject.h"

class Subject;

class Observer
{
private:
public:
    virtual void update() { }
    virtual void registerSubject(Subject* subject) { }
};



#endif