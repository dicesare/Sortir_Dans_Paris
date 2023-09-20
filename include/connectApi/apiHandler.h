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

class APIHandler : public Observable {
public:
    APIHandler();
    void fetchData();
    std::map<std::string, nlohmann::json> fetchTodaysEvents();

private:
    std::map<std::string, nlohmann::json> makeRequest(const std::string& url);
    const std::string baseUrl;
};

#endif // APIHANDLER_H
