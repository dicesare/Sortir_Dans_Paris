#include "../../include/connectApi/concreteObserver.h"

ConcreteObserver::ConcreteObserver() : dataStorage() {}

void ConcreteObserver::update(const std::map<std::string, nlohmann::json>& newEvents)
{
	currentAndUpcomingEvents = newEvents;
	// Maintenant, mettez à jour le dataset et retirez les événements expirés
	dataStorage.saveToFile(newEvents, "dataStorageSortirDansParis.json");
}
void ConcreteObserver::dailyUpdate(const std::map<std::string, nlohmann::json>& newDailyEvents)
{
	currentAndUpcomingEvents = newDailyEvents;
	// Maintenant, mettez à jour le dataset et retirez les événements expirés
	dataStorage.saveToFile(newDailyEvents, "updateDailyDataStorageSortirDansParis.json");
}
void ConcreteObserver::removeExpiredEvents()
{
	std::map<std::string, nlohmann::json> currentEvents = dataStorage.readFromFile("dataStorageSortirDansParis.json");
	std::time_t timeNow = std::time(nullptr);
	char buffer[11];
	std::strftime(buffer, 11, "%Y-%m-%d", std::localtime(&timeNow));
	std::string currentDate(buffer);

	for (auto it = currentEvents.begin(); it!= currentEvents.end();) {
		std::string eventDate = it->second;
		if (eventDate < currentDate) {
			it = currentEvents.erase(it);
		} else {
			++it;
		}
	}
	dataStorage.saveToFile(currentEvents, "dataStorageSortirDansParis.json");
}
