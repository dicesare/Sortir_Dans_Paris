// DataStorage.cpp
#include "../../include/storage/dataStorage.h"

DataStorage::DataStorage() : fileHelper() {}


void DataStorage::saveToFile(const std::map<std::string, nlohmann::json>& newData, const std::string& filename)
{    
    std::string filePath = fileHelper.getFilePath(filename);
    if(filePath != ""){        
        std::map<std::string, nlohmann::json> existingData;

        // Vérifiez si le fichier existe
        if (fileHelper.fileExists(filePath)) {
            std::ifstream i(filePath);
            nlohmann::json j;
            i >> j;
            existingData = j.at("events").get<std::map<std::string, nlohmann::json>>();//icii pour l'instant l'erreur
        }

        // Fusionnez les données existantes et les nouvelles données
        existingData.insert(newData.begin(), newData.end());
        std::ofstream o(filePath);
        if (o.is_open()) {
            nlohmann::json j;
            j["events"] = existingData;
            o << j.dump(4);
        } else {
            std::cerr << "Impossible d'ouvrir le fichier pour l'écriture." << std::endl;
        }
    } else {
        std::cerr << "Impossible de récupérer le répertoire personnel de l'utilisateur." << std::endl;
    }
}

std::map<std::string, nlohmann::json> DataStorage::readFromFile(const std::string& filename)
{
    std::string filePath = fileHelper.getFilePath(filename);
    if(filePath != ""){   
        
        std::map<std::string, nlohmann::json> existingData;

        // Vérifiez si le fichier existe
        if (fileHelper.fileExists(filePath)) {
            std::ifstream i(filePath);
            nlohmann::json j;
            i >> j;
            existingData = j.at("events").get<std::map<std::string, nlohmann::json>>();
        }

        return existingData;
    } else {
        std::cerr << "Impossible de récupérer le répertoire personnel de l'utilisateur." << std::endl;
        return std::map<std::string, nlohmann::json>();
    }
}