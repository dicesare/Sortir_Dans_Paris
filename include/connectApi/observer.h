#ifndef OBSERVER_H
#define OBSERVER_H

#include <string>
#include <iostream>

using namespace std;

class Observer {
public:
    virtual void update(const string& message) = 0;
};

#endif // OBSERVER_H
