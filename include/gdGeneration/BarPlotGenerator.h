/**
 * @file BarPlotGenerator.h
 * @author Antony Coco (antony.coco.pro@gmail.com)
 * @brief Header for the BarPlotGenerator class that manages bar plot creation.
 * @version 0.1
 * @date 2023-09-22
 * @copyright Copyright (c) 2023
 */

#ifndef BARPLOTGENERATOR_H
#define BARPLOTGENERATOR_H

#define FONT_PATH "/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf"
#define SIZE_TITLE 64
#define WIDTH 4000
#define HEIGHT 3000

// System and library headers
#include <map>
#include <string>
#include <gd.h> // GD Library
#include <gdfonts.h> // GD Library
#include <nlohmann/json.hpp>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <cctype>
#include <vector>
#include <iostream>
#include <random>

// Project headers
#include "../fileManagement/fileHelper.h"
#include "utils.h"
#include "GraphicsUtils.h"

/**
 * @brief Responsible for generating bar plots based on given data.
 * 
 * This class provides functionalities to generate bar plots using the GD library. 
 * It also manages the data preparation, loading, and saving of the generated images.
 */
class BarPlotGenerator {
public:
    BarPlotGenerator(); ///< Constructor of the class.
    ~BarPlotGenerator(); ///< Destructor of the class.

    /**
     * @brief Generates a random RGB color.
     * 
     * @return Color Randomly generated RGB color.
     */
    Color generate_random_color();

    /**
     * @brief Loads data from a given JSON map.
     * 
     * @param jsonData JSON data in a map format.
     */
    void loadDataFromJson(const std::map<std::string, nlohmann::json>& jsonData);

    /**
     * @brief Generates a bar plot image and saves it.
     * 
     * @param outputFilename The name of the output image file.
     */
    void generateBarPlot(const std::string& outputFilename);

    /**
     * @brief Saves a given GD image to a specified file.
     * 
     * @param img GD image pointer.
     * @param filename Name of the file to save the image to.
     */
    void saveImage(gdImagePtr img, const std::string& filename);

private:
    FileHelper fileHelper; ///< Helper for file management operations.
    std::map<std::string, int> tagFrequency; ///< Map containing the frequency of each tag.

    /**
     * @brief Formats the title of the image.
     * 
     * @param filename The original filename to be formatted.
     * @return std::string Formatted title.
     */
    std::string formatTitle(const std::string& filename);

    /**
     * @brief Validates a given tag.
     * 
     * @param tag The tag to be validated.
     * @return true If the tag is valid.
     * @return false If the tag is invalid.
     */
    bool isValidTag(const std::string& tag);
};

#endif // BARPLOTGENERATOR_H
