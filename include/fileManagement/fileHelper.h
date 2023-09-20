#ifndef FILEHELPER_H
#define FILEHELPER_H

#include <string>
#include <filesystem>
#include <iostream>

class FileHelper {
public:
    FileHelper();
    void setSubfolder(const std::string& subfolder);
    std::string getSubfolder() const;

    void ensureDirectoryExists(const std::string& path);
    bool fileExists(const std::string& filePath);
    std::string getFilePath(const std::string& filename);

private:
    std::string m_subfolder; // Définissez le sous-dossier par défaut ici

};

#endif // FILEHELPER_H
