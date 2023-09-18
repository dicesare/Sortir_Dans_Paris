#ifndef CONCRETEOBSERVER_H
#define CONCRETEOBSERVER_H

#include "observer.h"

class ConcreteObserver : public Observer {
public:
    // ConcreteObserver() = default;
    void update(const std::string &message) override;
};

#endif // CONCRETEOBSERVER_H
