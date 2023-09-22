/**
 * @file Observable.h
 * @author Antony Coco (antony.coco.pro@gmail.com)
 * @brief Provides the Observable class as part of the Observer design pattern.
 * @details The Observable class (or subject) acts as the central point of communication.
 * Observers can subscribe or unsubscribe from the Observable. When the Observable undergoes 
 * changes, it notifies all its subscribers.
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
 * @class Observable
 * @brief Represents the subject (or observable) in the Observer design pattern.
 * @details The Observable class maintains a list of its subscribers and provides 
 * mechanisms to notify them upon state changes or specific events. This forms a 
 * central component in the Observer pattern, allowing for a decoupled interaction 
 * between various components of a system.
 */
class Observable {
protected:
    std::vector<Observer*> observers; ///< A collection of subscribers (observers) that listen to this observable.

public:
    /**
     * @brief Registers an observer to the observable.
     * @details This method allows an observer to express its interest in receiving 
     * updates from this observable by adding it to the list of subscribers.
     *
     * @param o A pointer to the observer that wishes to subscribe.
     */
    void addObserver(Observer* o);

    /**
     * @brief Unregisters an observer from the observable.
     * @details Removes an observer from the list of subscribers, ensuring that 
     * it will no longer receive notifications from this observable.
     *
     * @param o A pointer to the observer to be unsubscribed.
     */
    void removeObserver(Observer* o);

    /**
     * @brief Sends updates to all registered observers.
     * @details Iterates over the list of subscribed observers and invokes 
     * their update method, thereby informing them about the latest events.
     *
     * @param newEvents A collection of new events to be disseminated to the observers.
     */
    void notifyObservers(const std::map<std::string, nlohmann::json>& newEvents);

    /**
     * @brief Sends daily-specific updates to all observers.
     * @details Iterates over the list of observers and notifies them about 
     * daily-specific events using their `dailyUpdate` method.
     *
     * @param newDailyEvents A collection of events specific to the day.
     */
    void notifyDailyObservers(const std::map<std::string, nlohmann::json>& newDailyEvents);
};

#endif // OBSERVABLE_H
