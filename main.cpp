#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <atomic>
#include <csignal>
#include <mutex>
#include <cstdlib> // Pour std::exit()

#include "include/connectApi/apiHandler.h" 
#include "include/connectApi/concreteObserver.h"
#include "include/service/periodicFetcher.h"

std::atomic<bool> stopRequested(false); 
std::mutex mtx;
std::thread fetchThread; // Déclarez le thread en tant que variable globale

void signalHandler(int signum) {
    {
        std::lock_guard<std::mutex> lock(mtx);
        std::cout << "Signal reçu: " << signum << ". Arrêt demandé." << std::endl;
        stopRequested.store(true);
    }

    if(fetchThread.joinable()) {
        fetchThread.join(); // Assurez-vous que le thread est terminé proprement
    }

    std::exit(EXIT_SUCCESS); // Terminez le programme proprement
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
    fetchThread = std::thread(&PeriodicFetcher::start, &fetcher);

    std::cout << "Attente de l'arrêt du fetcher..." << std::endl;
    fetchThread.join();
    std::cout << "Fetcher arrêté. Fin du programme." << std::endl;// pour voir le programme s'interrompre rapidement reduire le chrono dans periodicFetcher.cpp (passer à 5 secondes par exemple)

    return 0;
}
