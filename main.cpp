#include <iostream>
#include <string>
#include <thread>
#include <chrono>

#include "include/connectApi/apiHandler.h" 
#include "include/connectApi/concreteObserver.h"
#include "include/service/periodicFetcher.h"
int main(int argc, char **argv) {

    ConcreteObserver observerUnique;
    // ConcreteObserver observerDaily;

    APIHandler apiHandlerForUnique;
    // APIHandler apiHandlerForDaily;

    apiHandlerForUnique.addObserver(&observerUnique);
    // apiHandlerForDaily.addObserver(&observerDaily);

    // // Appel à l'API et notification des observateurs
    apiHandlerForUnique.fetchData();
    /* // abonnement journalier evenement
    PeriodicFetcher fetcher(apiHandlerForDaily);
    std::thread fetchThread(&PeriodicFetcher::start, &fetcher);
    // Pause pour tester plusieur requete pour tester (modifier aussi le sleep_for dans periodicFetcher.cpp)
    //std::this_thread::sleep_for(std::chrono::seconds(10));
    cout << "...Sleep over" << endl;

    fetcher.stop();
    fetchThread.join();
    */

    return 0;
}
