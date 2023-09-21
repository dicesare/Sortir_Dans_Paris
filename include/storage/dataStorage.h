#ifndef DATASTORAGE_H
#define DATASTORAGE_H

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <nlohmann/json.hpp>

#include "../fileManagement/fileHelper.h"
class DataStorage
{
public:
    DataStorage();
    std::map<std::string, nlohmann::json> loadFromFile(const std::string& filename);
    void saveToFile(const std::map<std::string, nlohmann::json>& data, const std::string& filename);
    std::map<std::string, nlohmann::json> readFromFile(const std::string& filename);
private:
    FileHelper fileHelper;
};

#endif // DATASTORAGE_H
