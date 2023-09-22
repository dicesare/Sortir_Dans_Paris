/**
 * @file periodicFetcher.h
 * @author Antony Coco (antony.coco.pro@gmail.com)
 * @brief Provides the PeriodicFetcher class for periodic data fetching and processing.
 * @details The PeriodicFetcher class is responsible for periodic retrieval of data,
 *          processing the data, and updating any associated Observables. Furthermore,
 *          this class leverages the PieChartGenerator for visualization needs.
 * @version 0.1
 * @date 2023-09-22
 * @copyright Copyright (c) 2023
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

/**
 * @namespace FetchIntervalTimeUnit
 * @brief Contains definitions related to time unit intervals.
 */

using namespace FetchIntervalTimeUnit;

/**
 * @class PeriodicFetcher
 * @brief Handles periodic data fetching, processing, and notifying Observables.
 * @details The PeriodicFetcher class encapsulates functionality related to periodically 
 *          fetching data from an external source, processing that data, and subsequently 
 *          updating associated Observables. Additionally, it generates pie charts 
 *          using the PieChartGenerator class for visualization of the data.
 */
class PeriodicFetcher {
public:

    /**
     * @brief Construct a new Periodic Fetcher object.
     * @details Initializes the fetcher with specified parameters and sets up required configurations.
     * 
     * @param observable Reference to the Observable object that will be updated with fetched data.
     * @param interval Time interval for periodic data fetching.
     * @param unit The unit of the fetch interval (e.g., seconds, minutes, hours).
     */
    PeriodicFetcher(Observable& observable, int interval, fitu unit);

    /**
     * @brief Begin the periodic fetching and processing of data.
     * @details This method initiates the continuous loop that fetches, processes data and updates the Observables.
     *          The loop continues until a stop signal is received.
     */
    void start();

private:
    int fetchInterval; ///< Time duration specifying how often data is fetched.
    fitu timeUnit;     ///< Enumerated type representing the unit of fetch interval (e.g., SEC, MIN, HR).
    PieChartGenerator pieChartGen; ///< Object used for generating pie charts from the fetched data.
    Observable& observable; ///< Reference to Observable object to which updates are sent.
    std::atomic<bool> stopRequested; ///< Atomic flag indicating if the fetching process should be stopped.
    std::mutex mtx; ///< Mutex ensuring thread-safety during data fetch and processing.
    static PeriodicFetcher* instance; ///< Singleton instance of the PeriodicFetcher class.

    /**
     * @brief Log messages for debugging and monitoring purposes.
     * @details This function outputs messages to the console, which can be useful for debugging,
     *          error-handling, or monitoring the operation of the PeriodicFetcher.
     * 
     * @param message String containing the message to be logged.
     */
    void log(const std::string& message);
};

#endif // PERIODICFETCHER_H