#include "../../include/fileManagement/fileHelper.h"
#include "fileHelper.h"


FileHelper::FileHelper() : m_subfolder("resources") {}

void FileHelper::setSubfolder(const std::string& subfolder) {
    m_subfolder = subfolder;
}

std::string FileHelper::getSubfolder() const {
    return m_subfolder;
}

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
        std::string path = std::string(homeDir) + "/" + m_subfolder + "/";
        ensureDirectoryExists(path);
        return path + filename;
    } else {
        std::cerr << "Impossible de récupérer le répertoire personnel de l'utilisateur." << std::endl;
        return "";
    }
}