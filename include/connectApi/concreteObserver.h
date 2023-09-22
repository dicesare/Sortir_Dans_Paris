/**
 * @file ConcreteObserver.h
 * @author Antony Coco (antony.coco.pro@gmail.com)
 * @brief Concrete implementation of the Observer interface.
 * @version 0.1
 * @date 2023-09-22
 * @copyright Copyright (c) 2023
 */

#ifndef CONCRETEOBSERVER_H
#define CONCRETEOBSERVER_H

#include <map>
#include <nlohmann/json.hpp>
#include "observer.h"
#include "../storage/dataStorage.h"
#include "../gdGeneration/BarPlotGenerator.h"

/**
 * @brief Represents a specific observer that reacts to changes in the observable.
 * 
 * The ConcreteObserver class provides specific actions to perform in response to
 * the changes in the observable subject. It holds its internal state, which is updated
 * upon receiving notifications from the observable subject. This class also has the capability
 * to generate a bar plot from the data it receives.
 */
class ConcreteObserver : public Observer {
private:
    std::map<std::string, nlohmann::json> currentAndUpcomingEvents; ///< Holds the current and upcoming events.
    DataStorage dataStorage; ///< Data storage mechanism for the observer.
    BarPlotGenerator barPlotGenerator; ///< Tool for generating bar plots from data.

    /**
     * @brief Generates a bar plot from the provided tag data.
     * 
     * @param newTagsJson Data represented in JSON format, used to generate the bar plot.
     */
    void generateBarPlotFromData(const std::map<std::string, nlohmann::json>& newTagsJson);

public:
    /**
     * @brief Default constructor for the ConcreteObserver.
     */
    ConcreteObserver();

    /**
     * @brief Overrides the Observer interface's update method.
     * 
     * On being notified of new events, this method updates the observer's internal state and may
     * trigger other relevant methods, such as generating a bar plot.
     * 
     * @param newEvents Data about the new events, represented as a map.
     */
    void update(const std::map<std::string, nlohmann::json>& newEvents) override;

    /**
     * @brief Overrides the Observer interface's dailyUpdate method.
     * 
     * Provides daily specific updates to the observer, updating its state and possibly triggering
     * other actions.
     * 
     * @param newDailyEvents Data about the new daily events, represented as a map.
     */
    void dailyUpdate(const std::map<std::string, nlohmann::json>& newDailyEvents) override;

    /**
     * @brief Removes expired events from the observer's state.
     * 
     * This method is responsible for cleaning up and ensuring that the observer's state remains
     * up-to-date by removing events that are no longer relevant.
     */
    void removeExpiredEvents() override;
};

#endif // CONCRETEOBSERVER_H
