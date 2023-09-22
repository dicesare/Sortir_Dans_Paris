// DataStorage.cpp
#include "../../include/storage/dataStorage.h"

DataStorage::DataStorage() : fileHelper() {}

// Helper function to validate and get the file path
std::string DataStorage::getValidFilePath(const std::string& filename) {
    std::string filePath = fileHelper.getFilePath(filename);
    if(filePath.empty()) {
        throw std::runtime_error("Unable to retrieve the user's home directory.");
    }
    return filePath;
}

void DataStorage::saveToFile(const std::map<std::string, nlohmann::json>& newData, const std::string& filename)
{    
    std::string filePath = getValidFilePath(filename);

    std::map<std::string, nlohmann::json> existingData;

    // Check if the file already exists
    if (fileHelper.fileExists(filePath)) {
        std::ifstream i(filePath);
        if (!i.is_open() || !i.good()) {
            throw std::runtime_error("Error opening file for reading.");
        }
        nlohmann::json j;
        i >> j;
        i.close();
        existingData = j.at("events").get<std::map<std::string, nlohmann::json>>();
    }

    // Merge the existing and new data
    existingData.insert(newData.begin(), newData.end());
    
    std::ofstream o(filePath);
    if (!o.is_open() || !o.good()) {
        throw std::runtime_error("Unable to open file for writing.");
    }
    nlohmann::json j;
    j["events"] = existingData;
    o << j.dump(4);
    o.close();
}

std::map<std::string, nlohmann::json> DataStorage::readFromFile(const std::string& filename)
{
    std::string filePath = getValidFilePath(filename);
        
    std::map<std::string, nlohmann::json> existingData;

    // Check if the file exists
    if (fileHelper.fileExists(filePath)) {
        std::ifstream i(filePath);
        if (!i.is_open() || !i.good()) {
            throw std::runtime_error("Error opening file for reading.");
        }
        nlohmann::json j;
        i >> j;
        i.close();
        existingData = j.at("events").get<std::map<std::string, nlohmann::json>>();
    }

    return existingData;
}
