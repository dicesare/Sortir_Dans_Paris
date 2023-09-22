#ifndef PERIODICFETCHER_H
#define PERIODICFETCHER_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <thread>
#include <chrono>
#include <mutex>
#include <atomic>
#include <csignal>

#include "../connectApi/observable.h"
#include "../connectApi/apiHandler.h"
#include "../gdGeneration/PieChartGenerator.h"

class PeriodicFetcher {
public:
    PeriodicFetcher(Observable& observable);
    void start();

private:
    PieChartGenerator pieChartGen;
    Observable& observable;
    std::atomic<bool> stopRequested;
    std::mutex mtx;

    static PeriodicFetcher* instance; // Déclaration du pointeur statique vers l'instance
    static void signalHandler(int signum);
};

#endif // PERIODICFETCHER_H
