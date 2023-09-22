/**
 * @file dataStorage.h
 * @author Antony Coco (antony.coco.pro@gmail.com)
 * @brief Provides the DataStorage class for handling data persistence in JSON format.
 * @details This header defines the DataStorage class which offers methods for saving and
 * reading JSON data from files. It utilizes the nlohmann::json library for JSON processing
 * and the FileHelper class for file management.
 * @version 0.1
 * @date 2023-09-22
 * @copyright Copyright (c) 2023
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
  * @class DataStorage
  * @brief Responsible for persisting data in JSON format.
  * @details The class allows saving of data items to files and reading them back. Data items are
  *          represented as JSON objects and are mapped to string keys for easy access and manipulation.
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
     * @details Reads existing data from the file (if it exists), merges with the new data, and saves 
     *          the combined data back to the file.
     * @param data The data to be saved.
     * @param filename The name of the file to which the data will be saved.
     */
    void saveToFile(const std::map<std::string, nlohmann::json>& data, const std::string& filename);

    /**
     * @brief Reads data from the given file.
     * @details Accesses the given file and extracts the stored JSON data. The data is then 
     *          returned in the form of a map.
     * @param filename The name of the file from which to read the data.
     * @return std::map<std::string, nlohmann::json> A map of data items.
     */
    std::map<std::string, nlohmann::json> readFromFile(const std::string& filename);

private:
    FileHelper fileHelper; ///< Helper object for file-related operations.

    /**
     * @brief Helper function to validate and get the file path.
     * @details Uses the FileHelper object to retrieve the file path and checks its validity.
     *          If it's invalid, throws an exception.
     * @param filename The name of the file for which to get the path.
     * @return std::string The valid file path for the given filename.
     * @throws std::runtime_error if unable to retrieve the user's home directory.
     */
    std::string getValidFilePath(const std::string& filename);
};

#endif // DATASTORAGE_H
