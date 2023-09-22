#ifndef BARPLOTGENERATOR_H
#define BARPLOTGENERATOR_H

#define FONT_PATH "/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf"
#define SIZE_TITLE 64
#define WIDTH 4000
#define HEIGHT 3000

#include <map>
#include <string>
#include <gd.h> // Bibliothèque GD
#include <gdfonts.h> // Bibliothèque GD
#include <nlohmann/json.hpp>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <cctype>
#include <vector>
#include <iostream> 
#include <random>

#include "../fileManagement/fileHelper.h"
#include "utils.h"
#include "GraphicsUtils.h"


class BarPlotGenerator {
public:
    BarPlotGenerator();
    ~BarPlotGenerator();

    Color generate_random_color();
    
    void loadDataFromJson(const std::map<std::string, nlohmann::json>& jsonData);
    void generateBarPlot(const std::string& outputFilename);
    void saveImage(gdImagePtr img, const std::string& filename);
private:
    FileHelper fileHelper;
    std::map<std::string, int> tagFrequency;
    bool isValidTag(const std::string& tag);
    std::string formatTitle(const std::string& filename);
};

#endif // BARPLOTGENERATOR_H