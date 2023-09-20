#ifndef FILEHELPER_H
#define FILEHELPER_H

#include <string>
#include <filesystem>
#include <iostream>

class FileHelper {
public:
    static void ensureDirectoryExists(const std::string& path);
    static bool fileExists(const std::string& filePath);
    static std::string getFilePath(const std::string& filename);

};

#endif // FILEHELPER_H
