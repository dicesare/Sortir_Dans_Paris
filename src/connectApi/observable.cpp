#include "../../include/connectApi/observable.h"

void Observable::addObserver(Observer* observer)
{
    observers.push_back(observer);
}

void Observable::removeObserver(Observer* observer)
{
    observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
}

void Observable::notifyObservers(const std::map<std::string, nlohmann::json>& newEvents)
{
    for (auto observer : observers)
    {
        observer->update(newEvents);
    }
}
void Observable::notifyDailyObservers(const std::map<std::string, nlohmann::json>& newDailyEvents)
{
    std::cout << "Notification: " << observers.size() << " observer(s) in list." << std::endl;
    for (auto observer : observers)
    {
        observer->dailyUpdate(newDailyEvents);
    }
}

