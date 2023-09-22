#include "../../include/service/periodicFetcher.h"

PeriodicFetcher* PeriodicFetcher::instance = nullptr;

PeriodicFetcher::PeriodicFetcher(Observable& observable, int interval, fitu unit)
    : observable(observable), stopRequested(false), pieChartGen(), fetchInterval(interval), timeUnit(unit) {
    SignalHandler::getInstance().setupSignalHandlers(); //// Setup signal handlers
}

void PeriodicFetcher::start() {
    APIHandler apiHandler;
    while (!SignalHandler::getInstance().isShutdownRequested()) {
        {
            std::lock_guard<std::mutex> lock(mtx);
            std::map<std::string, nlohmann::json> newEvents = apiHandler.fetchTodaysEvents();
            observable.notifyDailyObservers(newEvents);
            pieChartGen.generatePieChart(newEvents);
        }
        
        // Sleep for the configured fetch interval.
        switch (timeUnit) {
            case fitu::SEC:
                std::this_thread::sleep_for(std::chrono::seconds(fetchInterval));
                break;
            case fitu::MIN:
                std::this_thread::sleep_for(std::chrono::minutes(fetchInterval));
                break;
            case fitu::HR:
                std::this_thread::sleep_for(std::chrono::hours(fetchInterval));
                break;
            default:
                std::cerr << "Intervalle non reconnu!" << std::endl;
                return;
        }
    }

    std::cout << "[PeriodicFetcher] Arrêt en cours..." << std::endl;
    std::cout << "[PeriodicFetcher] Thread fetcher : arrêté." << std::endl;
}
