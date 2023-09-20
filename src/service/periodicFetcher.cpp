#include "../../include/service/periodicFetcher.h"

void PeriodicFetcher::start()
{
    APIHandler apiHandler;
    while (!stopFetching) {
        std::map<std::string, nlohmann::json> newEvents = apiHandler.fetchTodaysEvents();
        observable.notifyDailyObservers(newEvents);
        pieChartGen.generatePieChart(newEvents);
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }
}