#ifndef OBSERVABLE_H
#define OBSERVABLE_H

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <nlohmann/json.hpp>

#include "observer.h"


class Observable {
protected:
    std::vector<Observer*> observers;

public:
    void addObserver(Observer* o);
    void removeObserver(Observer* o);
    void notifyObservers(const std::map<std::string, nlohmann::json>& newEvents);
    void notifyDailyObservers(const std::map<std::string, nlohmann::json>& newDailyEvents);

};

#endif // OBSERVABLE_H
