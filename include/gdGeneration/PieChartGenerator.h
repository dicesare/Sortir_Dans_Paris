/**
 * @file PieChartGenerator.h
 * @author Antony Coco (antony.coco.pro@gmail.com)
 * @brief Provides functionality to generate pie charts using the GD library.
 * @version 0.1
 * @date 2023-09-22
 * @copyright Copyright (c) 2023
 *
 */

#ifndef PIECHARTGENERATOR_H
#define PIECHARTGENERATOR_H

#define FONT_PATH "/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf"
#define SIZE_TITLE 64
#define WIDTH 4000
#define HEIGHT 3000

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
#include "../fileManagement/fileHelper.h"
#include "utils.h"
#include "GraphicsUtils.h"

 /**
  * @brief Structure to represent a segment in a pie chart.
  *
  * This structure is used to define a segment of a pie chart, including
  * its percentage representation, label, and color.
  */
typedef struct PieChartSegment {
    double percentage;      ///< The percentage that this segment represents in the pie chart.
    std::string label;      ///< The label for this segment (e.g., the name of the category).
    Color color;            ///< The color used to draw this segment in the pie chart.
} PieChartSegment;

/**
 * @brief Class responsible for generating pie charts.
 *
 * This class provides the necessary methods and tools to generate pie charts based
 * on input data. The charts are generated using the GD library.
 */
class PieChartGenerator {
public:
    PieChartGenerator();
    ~PieChartGenerator();
    /**
     * @brief Loads data from the given file.
     *
     * @param filename The name of the file from which to load the data.
     * @return std::map<std::string, nlohmann::json> A map of data items, where each key-value pair
     * represents a unique data item identified by the string key and its corresponding JSON value.
     */
    Color generate_random_color(); ///< Generates a random color.
    /**
     * @brief Loads data from the given file.
     *
     * @param filename The name of the file from which to load the data.
     * @return std::map<std::string, nlohmann::json> A map of data items, where each key-value pair
     * represents a unique data item identified by the string key and its corresponding JSON value.
     */
    void generatePieChart(const std::map<std::string, nlohmann::json>& dataForPie); ///< Generates a pie chart based on the input data.

private:
    FileHelper fileHelper;
    /**
     * @brief Creates an image representing the pie chart.
     *
     * @param segments Array of segments to be drawn in the pie chart.
     * @param segments_count The number of segments.
     * @param title The title of the pie chart.
     * @return gdImagePtr Pointer to the generated image.
     */
    gdImagePtr create_pie_chart_image(PieChartSegment* segments, int segments_count, const char* title);
    /**
     * @brief Calculates the coordinates for a given angle on the pie chart.
     *
     * @param x The x-coordinate of the pie chart's center.
     * @param y The y-coordinate of the pie chart's center.
     * @param radius The radius of the pie chart.
     * @param angle The angle at which to calculate the coordinates.
     * @param coord_x Pointer to store the calculated x-coordinate.
     * @param coord_y Pointer to store the calculated y-coordinate.
     */
    void calculate_coordinates(int x, int y, int radius, int angle, int* coord_x, int* coord_y);
    /**
     * @brief Draws a segment and its corresponding label on the pie chart image.
     *
     * @param img The image on which to draw.
     * @param segments The array of segments.
     * @param length The number of segments.
     * @param x The x-coordinate of the pie chart's center.
     * @param y The y-coordinate of the pie chart's center.
     * @param start_angle The starting angle for the segment.
     * @param radius The radius of the pie chart.
     * @param black The color to use for drawing (usually black).
     */
    void draw_segment_and_label(gdImagePtr img, PieChartSegment* segments, int length, int x, int y, double start_angle, int radius, int black);
    /**
     * @brief Draws the title of the pie chart on the image.
     *
     * @param img The image on which to draw.
     * @param title The title to draw.
     * @param x The x-coordinate for the title.
     * @param y The y-coordinate for the title.
     * @param color The color to use for the title text.
     */
    void draw_title(gdImagePtr img, const char* title, int x, int y, int color);
    /**
     * @brief Saves the pie chart image to a file.
     *
     * @param img The pie chart image.
     * @param filename The name of the file where the image will be saved.
     */
    void saveImage(gdImagePtr img, const std::string& filename);
};

#endif // PIECHARTGENERATOR_H
