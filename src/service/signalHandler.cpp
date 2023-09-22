#include "../../include/service/signalHandler.h"

std::atomic<bool> SignalHandler::shutdownRequested(false);

SignalHandler& SignalHandler::getInstance() {
    static SignalHandler instance; // Lazily initialized singleton instance.
    return instance;
}

SignalHandler::SignalHandler() {}

SignalHandler::~SignalHandler() {}

void SignalHandler::setupSignalHandlers() {
    std::signal(SIGINT, handleSignal); // Setting up signal handler for SIGINT.
}

bool SignalHandler::isShutdownRequested() const {
    return shutdownRequested.load(); // Checking if shutdown is requested.
}

void SignalHandler::handleSignal(int signum) {
    if (signum == SIGINT) {
        std::cout << "Received signal: " << signum << ". Shutdown requested." << std::endl;
        shutdownRequested.store(true); // Indicating that shutdown is requested.
    }
}
