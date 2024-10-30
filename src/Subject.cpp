#include "Subject.h"


void Subject::notifyObservers()
{
    for (auto* observer : this->observers)
    {
        observer->update();
    }
}

void Subject::registerObserver(Observer* observer)
{
    observers.push_back(observer);
    observer->registerSubject(this);
}