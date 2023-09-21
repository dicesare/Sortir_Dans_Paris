#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <atomic>
#include <csignal>
#include <mutex>

#include "include/connectApi/apiHandler.h" 
#include "include/connectApi/concreteObserver.h"
#include "include/service/periodicFetcher.h"

std::atomic<bool> stopRequested(false); 
std::mutex mtx;

void signalHandler(int signum) {
    std::lock_guard<std::mutex> lock(mtx);
    std::cout << "Signal reçu: " << signum << ". Arrêt demandé." << std::endl;
    stopRequested.store(true);
}

int main(int argc, char **argv) {
    std::signal(SIGINT, signalHandler);

    ConcreteObserver observerUnique;
    ConcreteObserver observerDaily;

    APIHandler apiHandlerForUnique;
    APIHandler apiHandlerForDaily;

    apiHandlerForUnique.addObserver(&observerUnique);
    apiHandlerForDaily.addObserver(&observerDaily);

    // Appel à l'API et notification des observateurs
    apiHandlerForUnique.fetchData();
    
    PeriodicFetcher fetcher(apiHandlerForDaily);
    std::thread fetchThread(&PeriodicFetcher::start, &fetcher);

    std::cout << "Attente de l'arrêt du fetcher..." << std::endl;
    fetchThread.join();
    std::cout << "Fetcher arrêté. Fin du programme." << std::endl;

    return 0;
}
