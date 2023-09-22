/**
 * @file signalHandler.h
 * @author Antony Coco (antony.coco.pro@gmail.com)
 * @brief
 * @version 0.1
 * @date 2023-09-22
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef SIGNALHANDLER_H
#define SIGNALHANDLER_H

#include <csignal>
#include <atomic>
#include <iostream>
 /**
  * @brief
  *
  */
class SignalHandler {
public:
    /**
     * @brief Get the singleton instance of SignalHandler.
     * 
     * @return SignalHandler& Singleton instance.
     */
    static SignalHandler& getInstance();

    /**
     * @brief Set up signal handlers for the program.
     */
    void setupSignalHandlers();

    /**
     * @brief Check if a shutdown has been requested.
     * 
     * @return true if shutdown is requested.
     * @return false if no shutdown request.
     */
    bool isShutdownRequested() const;

private:
    SignalHandler();  ///< private constructor
    ~SignalHandler(); ///   ~private destructor
    /***
     *
    */
    SignalHandler(const SignalHandler&) = delete;
    /**
     * @brief
     *
     * @return SignalHandler&
     */
    SignalHandler& operator=(const SignalHandler&) = delete;
    /**
     * @brief Signal handler to gracefully stop the program.
     *
     * This function is called when the program receives a signal, such as SIGINT.
     * It stops the fetchThread and exits the program gracefully.
     *
     * @param signum The received signal number.
     */
    static void handleSignal(int signum);
    /**
     * @brief
     *
     */
    static std::atomic<bool> shutdownRequested; ///< Atomic flag indicating if shutdown is requested.
};

#endif // SIGNALHANDLER_H
