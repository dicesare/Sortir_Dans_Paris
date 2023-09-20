#ifndef DATASTORAGE_H
#define DATASTORAGE_H

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <nlohmann/json.hpp>

#include "../../include/fileManagement/fileHelper.h"
class DataStorage
{
public:
    static void saveToFile(const std::map<std::string, nlohmann::json>& data, const std::string& filename);
    static std::map<std::string, nlohmann::json> readFromFile(const std::string& filename);
};

#endif // DATASTORAGE_H
