#ifndef SUBJECT_CLASS_H
#define SUBJECT_CLASS_H

#include "Observer.h"

#include <vector>

class Observer;

class Subject
{
private:
    std::vector<Observer*> observers;
public:
    void notifyObservers();
    void registerObserver(Observer* observer);
    Subject() { }
    ~Subject() { }
};


#endif