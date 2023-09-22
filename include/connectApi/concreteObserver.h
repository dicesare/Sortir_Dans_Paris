#ifndef CONCRETEOBSERVER_H
#define CONCRETEOBSERVER_H

#include <map>
#include <nlohmann/json.hpp>
#include "observer.h"
#include "../storage/dataStorage.h"
#include "../gdGeneration/BarPlotGenerator.h"


class ConcreteObserver : public Observer {
private:
    std::map<std::string, nlohmann::json> currentAndUpcomingEvents;
    DataStorage dataStorage;
    BarPlotGenerator barPlotGenerator;
    void generateBarPlotFromData(const std::map<std::string, nlohmann::json>& newTagsJson);
public:
    ConcreteObserver();
    void update(const std::map<std::string, nlohmann::json>& newEvents) override;
    void dailyUpdate(const std::map<std::string, nlohmann::json>& newDailyEvents) override;
    void removeExpiredEvents() override;

};

#endif // CONCRETEOBSERVER_H
