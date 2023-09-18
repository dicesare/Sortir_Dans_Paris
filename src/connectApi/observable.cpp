#include "../../include/connectApi/observable.h"

void Observable::addObserver(Observer *o)
{
    observers.push_back(o);
}

void Observable::removeObserver(Observer *o)
{
    observers.erase(std::remove(observers.begin(), observers.end(), o), observers.end());
}

void Observable::notifyObservers(const std::string &message)
{
    for (auto o : observers)
    {
        o->update(message);
    }
}
