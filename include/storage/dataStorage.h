/**
 * @file dataStorage.h
 * @author Antony Coco (antony.coco.pro@gmail.com)
 * @brief Provides the DataStorage class for handling data persistence with JSON format.
 * @version 0.1
 * @date 2023-09-22
 * @copyright Copyright (c) 2023
 * 
 * This header defines the DataStorage class which facilitates saving and reading 
 * JSON data from files. The class leverages the nlohmann::json library 
 * for JSON parsing and the FileHelper class for file operations.
 */
#ifndef DATASTORAGE_H
#define DATASTORAGE_H

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <nlohmann/json.hpp>
#include "../fileManagement/fileHelper.h"

/**
 * @brief The DataStorage class handles the persistence of data in JSON format.
 * 
 * The class offers methods to save data to files and read data from files. 
 * Each data item is represented as a JSON object and is stored in a map with a string key.
 */
class DataStorage
{
public:
    /**
     * @brief Default constructor for DataStorage.
     */
    DataStorage();

    /**
     * @brief Saves the provided data to the given file.
     * 
     * @param data The data to be saved.
     * @param filename The name of the file to which the data will be saved.
     */
    void saveToFile(const std::map<std::string, nlohmann::json>& data, const std::string& filename);

    /**
     * @brief Reads data from the given file.
     * 
     * @param filename The name of the file from which to read the data.
     * @return std::map<std::string, nlohmann::json> A map of data items.
     */
    std::map<std::string, nlohmann::json> readFromFile(const std::string& filename);

private:
    FileHelper fileHelper; ///< Helper object for file-related operations.

    /**
     * @brief Helper function to validate and get the file path.
     * 
     * @param filename The name of the file for which to get the path.
     * @return std::string The valid file path for the given filename.
     * @throws std::runtime_error if unable to retrieve the user's home directory.
     */
    std::string getValidFilePath(const std::string& filename);
};

#endif // DATASTORAGE_H
