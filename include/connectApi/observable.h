#ifndef OBSERVABLE_H
#define OBSERVABLE_H

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>

#include "observer.h"


class Observable {
    std::vector<Observer*> observers;

public:
    void addObserver(Observer* o);
    void removeObserver(Observer* o);
    void notifyObservers(const string& message);

};

#endif // OBSERVABLE_H
