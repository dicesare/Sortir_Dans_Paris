#ifndef PERIODICFETCHER_H
#define PERIODICFETCHER_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <thread>
#include <chrono>
#include <mutex>

#include "../connectApi/observable.h"
#include "../connectApi/apiHandler.h"
#include "../gdGeneration/PieChartGenerator.h"

class PeriodicFetcher {
    
public:
    PeriodicFetcher(Observable& observable) : observable(observable), stopFetching(false), pieChartGen(){};

    void start();
    void stop() { stopFetching = true; }

private:
    PieChartGenerator pieChartGen;
    Observable& observable;
    bool stopFetching;
};


#endif // PERIODICFETCHER_H