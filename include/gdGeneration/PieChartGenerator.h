#ifndef PIECHARTGENERATOR_H
#define PIECHARTGENERATOR_H

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
#include "../fileManagement/fileHelper.h"
#include "utils.h"
/**
* @brief Structure to represent a color in the RGB color space.
*
* This structure is used to define a color using its red (r), green (g), and blue (b) components.
* It can be used to represent a specific color for various graphical elements.
*/
typedef struct Color
{
    int r; ///< Red component of the color, in the range 0-255.
    int g; ///< Green component of the color, in the range 0-255.
    int b; ///< Blue component of the color, in the range 0-255.
} Color;
/**
 * @brief Structure to represent a segment in a pie chart.
 *
 * This structure is used to define a segment of a pie chart, including
 * its percentage representation, label, and color.
 */
typedef struct PieChartSegment
{
    double percentage;      ///< The percentage that this segment represents in the pie chart.
    std::string label;         ///< The label for this segment (e.g., the name of the category).
    Color color;    ///< The color used to draw this segment in the pie chart.
} PieChartSegment;
/**
 * @brief Classe permettant de générer un graphique circulaire.
 *
 * Cette classe permet de générer un graphique circulaire à partir d'un tableau de données.
 * Le graphique est généré en utilisant la bibliothèque GD.
 */
class PieChartGenerator {
public:
    PieChartGenerator();
    void generatePieChart(const std::map<std::string, nlohmann::json>& dataForPie);
private:
    FileHelper fileHelper;

    gdImagePtr create_pie_chart_image(PieChartSegment* segments, int segments_count, const char* title);
    void calculate_coordinates(int x, int y, int radius, int angle, int* coord_x, int* coord_y);
    // void draw_label(gdImagePtr img, PieChartSegment* segments, int length, int x, int y, int start_angle, int radius, int color);
    void draw_segment_and_label(gdImagePtr img, PieChartSegment* segments, int length, int x, int y, double start_angle, int radius, int black);
    // void draw_pie_segments(gdImagePtr img, int x, int y, double start_angle, int radius, int black);
    void draw_title(gdImagePtr img, const char* title, int x, int y, int color);
    void saveImage(gdImagePtr img, const std::string& filename);
};


#endif // PIECHARTGENERATOR_H
