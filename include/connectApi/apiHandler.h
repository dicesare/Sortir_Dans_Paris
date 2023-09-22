/**
 * @file APIHandler.h
 * @author Antony Coco (antony.coco.pro@gmail.com)
 * @brief Handles API requests and notifies observers with the fetched data.
 * @version 0.1
 * @date 2023-09-22
 * @copyright Copyright (c) 2023
 */

#ifndef APIHANDLER_H
#define APIHANDLER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <variant>

#include "observable.h"

/**
 * @brief The APIHandler class is responsible for fetching data from a given API.
 * 
 * The class provides methods to make requests to an external API and process the returned
 * data. Once the data is fetched, it acts as an Observable, notifying its observers
 * of the new data. This class abstracts the details of making API requests and provides
 * a clean interface to obtain data for the application.
 */
class APIHandler : public Observable {
public:
    /**
     * @brief Default constructor for APIHandler.
     */
    APIHandler();

    /**
     * @brief Fetches data from the API and notifies its observers.
     * 
     * This method communicates with the base URL of the API, retrieves data,
     * and then notifies all registered observers with this new data.
     */
    void fetchData();

    /**
     * @brief Fetches today's events from the API.
     * 
     * @return std::map<std::string, nlohmann::json> A map containing data about today's events.
     */
    std::map<std::string, nlohmann::json> fetchTodaysEvents();

private:
    /**
     * @brief Makes a request to the provided URL and returns the fetched data.
     * 
     * @param url The specific URL endpoint to fetch data from.
     * @return std::map<std::string, nlohmann::json> A map containing the fetched data.
     */
    std::map<std::string, nlohmann::json> makeRequest(const std::string& url);

    const std::string baseUrl; ///< The base URL for the API.
};

#endif // APIHANDLER_H
