/**
 * @file signalHandler.h
 * @author Antony Coco (antony.coco.pro@gmail.com)
 * @brief Provides a singleton-based handler for system signals.
 * @details This header defines the SignalHandler class responsible for managing
 *          system signals (like SIGINT) to ensure graceful shutdown of the program.
 * @version 0.1
 * @date 2023-09-22
 * @copyright Copyright (c) 2023
 *
 */

#ifndef SIGNALHANDLER_H
#define SIGNALHANDLER_H

#include <csignal>
#include <atomic>
#include <iostream>

/**
 * @class SignalHandler
 * @brief Singleton-based handler for system signals.
 * 
 * The SignalHandler class provides methods to set up handlers for system signals,
 * particularly for enabling graceful shutdown mechanisms. Being designed as a 
 * singleton ensures that only one instance handles all signals in a consistent manner.
 */
class SignalHandler {
public:
    /**
     * @brief Retrieve the singleton instance of SignalHandler.
     * 
     * @return SignalHandler& Singleton instance of the SignalHandler.
     */
    static SignalHandler& getInstance();

    /**
     * @brief Initialize and set up signal handlers for the program.
     */
    void setupSignalHandlers();

    /**
     * @brief Determine if a shutdown signal has been received.
     * 
     * @return true if a shutdown signal is detected.
     * @return false otherwise.
     */
    bool isShutdownRequested() const;

private:
    /**
     * @brief Private constructor to ensure the singleton pattern.
     */
    SignalHandler();

    /**
     * @brief Private destructor to prevent external deletion.
     */
    ~SignalHandler();

    // Deleted copy constructor and assignment operator to prevent copy operations.
    SignalHandler(const SignalHandler&) = delete;
    SignalHandler& operator=(const SignalHandler&) = delete;

    /**
     * @brief Internal handler for system signals.
     * 
     * This function is invoked when specific signals (e.g., SIGINT) are received by 
     * the program. Its primary role is to set the shutdown flag, facilitating a 
     * graceful program termination.
     * 
     * @param signum The number of the received signal.
     */
    static void handleSignal(int signum);

    /**
     * @brief Atomic flag to track if a shutdown signal has been received.
     */
    static std::atomic<bool> shutdownRequested;
};

#endif // SIGNALHANDLER_H
