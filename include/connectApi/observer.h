#ifndef OBSERVER_H
#define OBSERVER_H

#include <string>
#include <iostream>
#include <map>
#include <nlohmann/json.hpp>

using namespace std;

class Observer {
public:
    virtual void update(const std::map<std::string, nlohmann::json>& newEvents) = 0;
    virtual void dailyUpdate(const std::map<std::string, nlohmann::json>& newDailyEvents) = 0;
    virtual void removeExpiredEvents() = 0;
};
#endif // OBSERVER_H
