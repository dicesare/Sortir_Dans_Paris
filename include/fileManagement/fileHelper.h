/**
 * @file FileHelper.h
 * @author Antony Coco (antony.coco.pro@gmail.com)
 * @brief Provides helper functions for file and directory operations.
 * @version 0.1
 * @date 2023-09-22
 * @copyright Copyright (c) 2023
 */

#ifndef FILEHELPER_H
#define FILEHELPER_H

#include <string>
#include <filesystem>
#include <iostream>

/**
 * @brief Utility class for file and directory management.
 * 
 * This class offers various utility functions for managing files and directories.
 * It simplifies certain tasks like checking if a file exists or ensuring the existence
 * of a directory.
 */
class FileHelper {
public:
    /**
     * @brief Default constructor.
     */
    FileHelper();

    /**
     * @brief Sets the subfolder path for operations.
     * 
     * This function sets the subfolder that is used for all subsequent file and directory operations.
     * 
     * @param subfolder The path of the subfolder to set.
     */
    void setSubfolder(const std::string& subfolder);

    /**
     * @brief Retrieves the currently set subfolder.
     * 
     * @return std::string The path of the currently set subfolder.
     */
    std::string getSubfolder() const;

    /**
     * @brief Ensures that a given directory exists.
     * 
     * If the specified directory does not exist, it will be created.
     * 
     * @param path The path of the directory to check or create.
     */
    void ensureDirectoryExists(const std::string& path);

    /**
     * @brief Checks if a file exists at the given path.
     * 
     * @param filePath The path of the file to check.
     * @return bool `true` if the file exists, `false` otherwise.
     */
    bool fileExists(const std::string& filePath);

    /**
     * @brief Constructs a complete file path using the current subfolder and the provided filename.
     * 
     * @param filename The name of the file.
     * @return std::string The complete path constructed using the subfolder and the filename.
     */
    std::string getFilePath(const std::string& filename);

private:
    std::string m_subfolder; ///< Defines the default subfolder here.

};

#endif // FILEHELPER_H
