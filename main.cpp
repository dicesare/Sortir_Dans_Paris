#include <iostream>
#include <string>
#include <thread>
#include <chrono>

#include "include/connectApi/apiHandler.h" 
#include "include/connectApi/concreteObserver.h"
#include "include/service/periodicFetcher.h"
int main() {

    ConcreteObserver observerUnique;
    ConcreteObserver observerDaily;

    APIHandler apiHandlerForUnique;
    APIHandler apiHandlerForDaily;

    apiHandlerForUnique.addObserver(&observerUnique);
    apiHandlerForDaily.addObserver(&observerDaily);

    // // Appel à l'API et notification des observateurs
    apiHandlerForUnique.fetchData();
    PeriodicFetcher fetcher(apiHandlerForDaily);
    std::thread fetchThread(&PeriodicFetcher::start, &fetcher);
    // Pause de 30 secondes pour tester
    std::this_thread::sleep_for(std::chrono::seconds(10));
    cout << "30 seconds passed" << endl;

    fetcher.stop();
    fetchThread.join();

    return 0;
}
