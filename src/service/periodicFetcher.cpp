#include "../../include/service/periodicFetcher.h"

PeriodicFetcher* PeriodicFetcher::instance = nullptr;

PeriodicFetcher::PeriodicFetcher(Observable& observable)
    : observable(observable), stopRequested(false), pieChartGen()
{
    if (!instance) {
        instance = this;
        // Associer le signal SIGINT (CTRL+C) à notre gestionnaire de signal
        std::signal(SIGINT, signalHandler);

    }
}

void PeriodicFetcher::signalHandler(int signum)
{
    std::cout << "[PeriodicFetcher] Signal d'arrêt reçu : " << signum << std::endl;
    if (instance) {
        instance->stopRequested.store(true);
    }
}

void PeriodicFetcher::start() {
    APIHandler apiHandler;
    while (!stopRequested.load()) {
        {
            std::lock_guard<std::mutex> lock(mtx);
            std::map<std::string, nlohmann::json> newEvents = apiHandler.fetchTodaysEvents();
            observable.notifyDailyObservers(newEvents);
            pieChartGen.generatePieChart(newEvents);
        }

        std::cout << "[PeriodicFetcher] Nouveaux événements récupérés et traités." << std::endl;

        std::this_thread::sleep_for(std::chrono::hours(1));

        std::cout << "[PeriodicFetcher] Thread fetcher : encore en exécution." << std::endl;
    }

    std::cout << "[PeriodicFetcher] Arrêt en cours..." << std::endl;
    std::cout << "[PeriodicFetcher] Thread fetcher : arrêté." << std::endl;
}
