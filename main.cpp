/**
 * @file main.cpp
 * @author Antony Coco (antony.coco.pro@gmail.com)
 * @brief Main program for fetching and visualizing events in Paris.
 * @version 0.1
 * @date 2023-09-22
 * 
 * @copyright Copyright (c) 2023
 * 
 * 
 */
#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <atomic>
#include <csignal>
#include <mutex>
#include <cstdlib> // For std::exit()

#include "include/connectApi/apiHandler.h" 
#include "include/connectApi/concreteObserver.h"
#include "include/service/periodicFetcher.h"

std::atomic<bool> stopRequested(false); 
std::mutex mtx;
std::thread fetchThread; // Declare the thread as a global variable

/**
 * @brief Signal handler to gracefully stop the program.
 * 
 * This function is called when the program receives a signal, such as SIGINT.
 * It stops the fetchThread and exits the program gracefully.
 * 
 * @param signum The received signal number.
 */
void signalHandler(int signum) {
    {
        std::lock_guard<std::mutex> lock(mtx);
        std::cout << "Received signal: " << signum << ". Shutdown requested." << std::endl;
        stopRequested.store(true);
    }

    if(fetchThread.joinable()) {
        fetchThread.join(); // Ensure the thread finishes cleanly
    }

    std::exit(EXIT_SUCCESS); // Exit the program gracefully
}

/**
 * @brief Main function of the program.
 * 
 * This function initializes the observers, API handlers, and the periodic fetcher.
 * It also launches a thread for the periodic fetcher and waits for its completion.
 * 
 * @param argc Command line argument count.
 * @param argv Command line argument vector.
 * @return int Return code of the program.
 */
int main(int argc, char **argv) {
    std::signal(SIGINT, signalHandler);

    ConcreteObserver observerUnique;
    ConcreteObserver observerDaily;

    APIHandler apiHandlerForUnique;
    APIHandler apiHandlerForDaily;

    apiHandlerForUnique.addObserver(&observerUnique);
    apiHandlerForDaily.addObserver(&observerDaily);

    // Fetch data from the API and notify observers
    apiHandlerForUnique.fetchData();
    
    PeriodicFetcher fetcher(apiHandlerForDaily);
    fetchThread = std::thread(&PeriodicFetcher::start, &fetcher);

    std::cout << "Waiting for fetcher to stop..." << std::endl;
    fetchThread.join();
    std::cout << "Fetcher stopped. Program terminated." << std::endl; // To see the program interrupt quickly, reduce the chrono in periodicFetcher.cpp (set to 5 seconds for instance)

    return 0;
}
