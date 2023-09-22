/**
 * @file Observable.h
 * @author Antony Coco (antony.coco.pro@gmail.com)
 * @brief Defines the Observable class for the Observer design pattern.
 * @version 0.1
 * @date 2023-09-22
 * @copyright Copyright (c) 2023
 */

#ifndef OBSERVABLE_H
#define OBSERVABLE_H

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <nlohmann/json.hpp>

#include "observer.h"

/**
 * @brief Represents the subject (or observable) in the Observer design pattern.
 *
 * The Observable class serves as the subject to which Observers can subscribe.
 * When the Observable object changes its state, it notifies all its subscribed Observers.
 * This allows for a dynamic and decoupled interaction between different parts of the system.
 */
class Observable {
protected:
    std::vector<Observer*> observers; ///< List of observers subscribed to this observable.

public:
    /**
     * @brief Adds an observer to the list of subscribed observers.
     *
     * @param o Pointer to the observer to be added.
     */
    void addObserver(Observer* o);

    /**
     * @brief Removes an observer from the list of subscribed observers.
     *
     * @param o Pointer to the observer to be removed.
     */
    void removeObserver(Observer* o);

    /**
     * @brief Notifies all subscribed observers of new events.
     *
     * This method loops through all the observers and invokes their `update` method,
     * effectively informing them about the new events.
     *
     * @param newEvents A map of new events to be shared with the observers.
     */
    void notifyObservers(const std::map<std::string, nlohmann::json>& newEvents);

    /**
     * @brief Notifies all subscribed observers with daily specific updates.
     *
     * This method loops through all the observers and invokes their `dailyUpdate` method,
     * effectively informing them about the daily-specific events.
     *
     * @param newDailyEvents A map of daily events to be shared with the observers.
     */
    void notifyDailyObservers(const std::map<std::string, nlohmann::json>& newDailyEvents);
};

#endif // OBSERVABLE_H
