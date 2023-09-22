/**
 * @file periodicFetcher.h
 * @author Antony Coco (antony.coco.pro@gmail.com)
 * @brief Provides the PeriodicFetcher class for periodic data fetching and processing.
 * @version 0.1
 * @date 2023-09-22
 * @copyright Copyright (c) 2023
 * 
 * This header defines the PeriodicFetcher class that periodically fetches 
 * data, processes it, and interacts with Observables. It also manages chart 
 * generation using the PieChartGenerator.
 */
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
#include "fetchIntervalTimeUnit.h"
#include "signalHandler.h"

using namespace FetchIntervalTimeUnit;

/**
 * @brief The PeriodicFetcher class handles periodic data fetching and processing.
 * 
 * The class fetches data at regular intervals, processes it, and updates 
 * any associated Observables. It also uses PieChartGenerator for generating charts.
 */
class PeriodicFetcher {
public:
    /**
     * @brief Construct a new Periodic Fetcher object
     * 
     * @param observable A reference to the Observable object to be updated.
     */
    PeriodicFetcher(Observable& observable, int interval, fitu unit);

    /**
     * @brief Starts the periodic fetching and processing of data.
     */
    void start();

private:
    int fetchInterval; ///< The fetch interval in seconds.
    fitu timeUnit; ///< The unit of the fetch interval.
    PieChartGenerator pieChartGen; ///< Object for pie chart generation.
    Observable& observable; ///< Reference to the Observable to be updated.
    std::atomic<bool> stopRequested; ///< Flag to indicate if stopping the fetcher is requested.
    std::mutex mtx; ///< Mutex for thread-safety.
    static PeriodicFetcher* instance; ///< Static pointer to the instance of PeriodicFetcher.
};

#endif // PERIODICFETCHER_H
