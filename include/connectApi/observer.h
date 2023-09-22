/**
 * @file Observer.h
 * @author Antony Coco (antony.coco.pro@gmail.com)
 * @brief Provides the Observer interface as part of the Observer design pattern.
 * @details The Observer design pattern enables a subject to keep its observers informed about any changes. 
 * In this design, this Observer class acts as the interface that all concrete observers must implement 
 * to receive and handle notifications from the subject.
 * @version 0.1
 * @date 2023-09-22
 * @copyright Copyright (c) 2023
 */

#ifndef OBSERVER_H
#define OBSERVER_H

#include <string>
#include <map>
#include <nlohmann/json.hpp>

/**
 * @class Observer
 * @brief Interface for the Observer in the Observer design pattern.
 * @details In the context of the Observer design pattern, this interface establishes the 
 * contract that all observers must fulfill. The observers are expected to receive updates 
 * about new events, daily activities, and the removal of expired events. Concrete observer 
 * classes should implement this interface to define their reactions to such notifications.
 */
class Observer {
public:
    /**
     * @brief Updates the Observer with general events.
     * @details This method notifies the observer about general events. Implementing classes 
     * should process and react to these events as per their specific requirements.
     * 
     * @param newEvents A map of the latest events represented as key-value pairs.
     */
    virtual void update(const std::map<std::string, nlohmann::json>& newEvents) = 0;

    /**
     * @brief Provides the Observer with daily-specific updates.
     * @details Observers receive daily-specific events via this method. Concrete observers 
     * should handle these events and adapt based on their individual business logic.
     * 
     * @param newDailyEvents A map of daily events characterized by key-value pairs.
     */
    virtual void dailyUpdate(const std::map<std::string, nlohmann::json>& newDailyEvents) = 0;

    /**
     * @brief Commands the Observer to address expired events.
     * @details Implementing classes should take the necessary actions upon receiving 
     * this instruction, such as removing or archiving the expired events.
     */
    virtual void removeExpiredEvents() = 0;
};

#endif // OBSERVER_H
