/**
 * @file FileHelper.h
 * @author Antony Coco (antony.coco.pro@gmail.com)
 * @brief Provides helper functions for file and directory operations.
 * @details This class offers functionalities that abstract and simplify common operations 
 * with files and directories, such as existence checks, directory creation, and path retrieval.
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
 * @class FileHelper
 * @brief Utility class for file and directory management.
 * @details This class streamlines common file and directory operations, making it easier 
 * to perform checks, retrieve paths, and ensure directories exist.
 */
class FileHelper {
public:
    FileHelper();

    /**
     * @brief Updates the default subfolder.
     * @details This function updates the internal subfolder path, which affects subsequent 
     * file and directory operations using this helper.
     * 
     * @param subfolder New subfolder path.
     */
    void setSubfolder(const std::string& subfolder);

    /**
     * @brief Retrieves the active subfolder path.
     * @details This function fetches the currently set subfolder path, which is used 
     * in other operations of the FileHelper.
     * 
     * @return std::string Active subfolder path.
     */
    std::string getSubfolder() const;

    /**
     * @brief Makes sure the provided directory exists.
     * @details This function checks for the existence of a directory at the given path. 
     * If the directory does not exist, it attempts to create it.
     * 
     * @param path Path to the directory to ensure.
     */
    void ensureDirectoryExists(const std::string& path);

    /**
     * @brief Verifies if a file exists at the provided path.
     * @details This function checks the existence of a file at the specified path 
     * and returns a boolean value indicating its presence.
     * 
     * @param filePath Path to the file to check.
     * @return bool `true` if file exists, otherwise `false`.
     */
    bool fileExists(const std::string& filePath);

    /**
     * @brief Constructs the full path for a file using the current subfolder.
     * @details This function constructs a complete file path by appending the filename to 
     * the currently set subfolder. Additionally, it ensures the existence of the directory 
     * before returning the path.
     * 
     * @param filename The file name to use for path construction.
     * @return std::string Constructed file path.
     */
    std::string getFilePath(const std::string& filename);

private:
    std::string m_subfolder; ///< Defines the default subfolder here.
};

#endif // FILEHELPER_H