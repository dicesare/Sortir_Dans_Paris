/**
 * @file main.cpp
 * @author Antony Coco (antony.coco.pro@gmail.com)
 * @brief Main program to orchestrate the fetching and visualization of events in Paris.
 * @details The program fetches data from an external API both at regular intervals 
 *          and upon program initialization, processes this data, and provides 
 *          visualization capabilities.
 * @version 0.1
 * @date 2023-09-22
 * @copyright Copyright (c) 2023
 */

#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <cstdlib> // For std::exit()

#include "include/connectApi/apiHandler.h" 
#include "include/connectApi/concreteObserver.h"
#include "include/service/periodicFetcher.h"
#include "include/service/signalHandler.h"
#include "include/service/fetchIntervalTimeUnit.h"

/**
 * @namespace FetchIntervalTimeUnit
 * @brief Defines time unit intervals for periodic fetching.
 */

using namespace FetchIntervalTimeUnit;

std::thread fetchThread; ///< Thread for executing periodic fetch operations.

/**
 * @brief Converts string representation of a time unit to its corresponding enum value.
 * @details This utility function is used primarily for parsing command-line arguments.
 *
 * @param str String representation of the time unit (e.g., "sec", "min", "hr").
 * @return FetchIntervalTimeUnit::fitu Enumerated value corresponding to the provided string.
 */
FetchIntervalTimeUnit::fitu stringToTimeUnit(const std::string& str);

int main(int argc, char** argv) {
    int fetchInterval = 1; ///< Default fetch interval value, e.g., 1 hour.
    fitu unit = fitu::HR; ///< Default time unit, e.g., hour.

    // Parse command-line arguments
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--thread" || arg == "-T") {
            if (i + 1 < argc) {
                std::string value = argv[i + 1];
                size_t pos;
                int num = std::stoi(value, &pos);
                fitu timeUnitEnum = stringToTimeUnit(value.substr(pos));

                // Assign appropriate time unit and interval based on parsed values.
                switch (timeUnitEnum) {
                case fitu::SEC:
                    unit = fitu::SEC;
                    fetchInterval = num;
                    break;
                case fitu::MIN:
                    unit = fitu::MIN;
                    fetchInterval = num;
                    break;
                case fitu::HR:
                    unit = fitu::HR;
                    fetchInterval = num;
                    break;
                default:
                    unit = fitu::UNKNOWN;
                    std::cerr << "Unité de temps non reconnue: " << value.substr(pos) << std::endl;
                    return 1;
                }
            }
        }
    }

    // Setup signal handlers for managing program's lifecycle (e.g., graceful shutdown).
    SignalHandler::getInstance().setupSignalHandlers();

    ConcreteObserver observerUnique; ///< Observer instance dedicated to unique event data.
    ConcreteObserver observerDaily;  ///< Observer instance dedicated to daily event data.

    APIHandler apiHandlerForUnique; ///< API handler tailored for fetching unique event data.
    APIHandler apiHandlerForDaily;  ///< API handler tailored for fetching daily event data.

    // Register observers
    apiHandlerForUnique.addObserver(&observerUnique);
    apiHandlerForDaily.addObserver(&observerDaily);

    // Initial fetch of data for unique events
    apiHandlerForUnique.fetchData();

    // Initialize periodic fetcher and start it in a separate thread.
    PeriodicFetcher fetcher(apiHandlerForDaily, fetchInterval, unit);
    fetchThread = std::thread(&PeriodicFetcher::start, &fetcher);

    // Main loop: Continuously run until an external shutdown signal is received.
    while (!SignalHandler::getInstance().isShutdownRequested()) {
        std::this_thread::sleep_for(std::chrono::seconds(1)); // Check for shutdown signal every second.
    }

    fetchThread.join(); // Ensure the fetch thread has finished.
    std::cout << "Program terminated due to shutdown request." << std::endl;
    return 0;
}

// Definition of the conversion utility function
FetchIntervalTimeUnit::fitu stringToTimeUnit(const std::string& str) {
    if (str == "sec") return fitu::SEC;
    if (str == "min") return fitu::MIN;
    if (str == "hr") return fitu::HR;
    return fitu::UNKNOWN;
}
