/**
 * @file Observer.h
 * @author Antony Coco (antony.coco.pro@gmail.com)
 * @brief Defines an Observer interface for the Observer design pattern.
 * @version 0.1
 * @date 2023-09-22
 * @copyright Copyright (c) 2023
 */

#ifndef OBSERVER_H
#define OBSERVER_H

#include <string>
#include <iostream>
#include <map>
#include <nlohmann/json.hpp>

/**
 * @brief Interface for the Observer in the Observer design pattern.
 * 
 * The Observer design pattern is used to create a one-to-many dependency 
 * between objects so that when one object changes its state, all its 
 * dependents are notified and updated automatically. This class provides 
 * the interface that Observers must implement to receive and process these notifications.
 */
class Observer {
public:
    /**
     * @brief Notify the Observer of new events.
     * 
     * Implementing classes should handle the update based on the received events.
     * 
     * @param newEvents A map of new events represented by key-value pairs.
     */
    virtual void update(const std::map<std::string, nlohmann::json>& newEvents) = 0;

    /**
     * @brief Notify the Observer of daily updates.
     * 
     * Implementing classes should handle daily-specific updates based on the received events.
     * 
     * @param newDailyEvents A map of daily events represented by key-value pairs.
     */
    virtual void dailyUpdate(const std::map<std::string, nlohmann::json>& newDailyEvents) = 0;

    /**
     * @brief Instruct the Observer to remove expired events.
     * 
     * Implementing classes should remove or handle any expired events.
     */
    virtual void removeExpiredEvents() = 0;
};

#endif // OBSERVER_H
