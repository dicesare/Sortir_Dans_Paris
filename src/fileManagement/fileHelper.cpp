#include "../../include/fileManagement/fileHelper.h"
#include "fileHelper.h"



void FileHelper::ensureDirectoryExists(const std::string& path)
{
    if (!std::filesystem::exists(path)) {
        std::filesystem::create_directories(path);
    }
}
bool FileHelper::fileExists(const std::string& filePath)
{
    return std::filesystem::exists(filePath);
}

std::string FileHelper::getFilePath(const std::string& filename) {
    const char* homeDir = getenv("HOME");
    if (homeDir) {
        std::string path = std::string(homeDir) + "/resources/";
        ensureDirectoryExists(path);
        return path + filename;
    } else {
        std::cerr << "Impossible de récupérer le répertoire personnel de l'utilisateur." << std::endl;
        return "";
    }
}