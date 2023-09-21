#include "../../include/gdGeneration/PieChartGenerator.h"
#include "PieChartGenerator.h"

PieChartGenerator::PieChartGenerator() : fileHelper() {}
PieChartGenerator::~PieChartGenerator() {}


Color PieChartGenerator::generate_random_color()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, 255);
    
    Color color;
    color.r = distrib(gen);
    color.g = distrib(gen);
    color.b = distrib(gen);
    return color;
    return Color();
}

void PieChartGenerator::generatePieChart(const std::map<std::string, nlohmann::json>& dataForPie) {
    std::map<std::string, int> zipCodeCounts; // Stocke le nombre d'événements pour chaque code postal
    std::vector<PieChartSegment> segments;

    // Extraire les codes postaux des données et les compter
    for (const auto& [id, data] : dataForPie) {
        if (data.contains("address_zipcode") && !data["address_zipcode"].is_null()) {
            std::string zipCodeString = data["address_zipcode"].get<std::string>();

            // Enlever tous les caractères qui ne sont pas des chiffres
            zipCodeString.erase(
                std::remove_if(
                    zipCodeString.begin(),
                    zipCodeString.end(),
                    [](unsigned char x) {return !std::isdigit(x);}), zipCodeString.end());

            // Vérifier si la chaîne est un code postal valide après avoir enlevé les caractères non numériques
            if (zipCodeString.length() >= 5) {
                zipCodeString = zipCodeString.substr(0, 5);
                zipCodeCounts[zipCodeString]++;
            }
        }
    }
    //afficher la somme de comptage total des count de zipCodeCounts
    int sommeCount = 0;
    for (const auto& count : zipCodeCounts) {
        sommeCount += count.second;
    }
    // Créer les segments du graphique
    for (const auto& [zipCode, count] : zipCodeCounts) {
        PieChartSegment segment;
        segment.percentage = (static_cast<double>(count) / sommeCount) * 100.0;
        segment.label = zipCode;
        segments.push_back(segment);
    }
    double otherPercentage = 0.0;
    std::vector<PieChartSegment> filteredSegments;

    // Trier les segments par ordre croissant de pourcentage
    std::sort(segments.begin(), segments.end(), [](const PieChartSegment& a, const PieChartSegment& b) {
        return a.percentage < b.percentage;
        });
    // Vérifier si le nombre de segments est supérieur à 34
    while (segments.size() > 34) {
        // Regrouper les plus petits segments en un seul segment "Autres"
        double otherPercentage = 0.0;
        while (segments.size() > 33) {  // 33 pour laisser de la place pour le segment "Autres"
            otherPercentage += segments.front().percentage;
            segments.erase(segments.begin());
        }

        PieChartSegment otherSegment;
        otherSegment.percentage = otherPercentage;
        otherSegment.label = "Autres";
        segments.push_back(otherSegment);
    }
    // Créer l'image du graphique
    gdImagePtr img = create_pie_chart_image(segments.data(), segments.size(), "Evenements par code postal");
    fileHelper.setSubfolder("resources/graphic");
    std::string output_path = fileHelper.getFilePath("pie_chart.png"); // Ou utilisez la méthode fileHelper pour obtenir le chemin complet
    saveImage(img, output_path);
}

gdImagePtr PieChartGenerator::create_pie_chart_image(PieChartSegment* segments, int segments_count, const char* title) {

    // Create a new image with predefined dimensions
    gdImagePtr img = gdImageCreate(WIDTH, HEIGHT);

    // Set a background color (adjust as required)
    int backgroundColor = gdImageColorAllocate(img, 255, 255, 255);  // Blanc
    gdImageFill(img, 0, 0, backgroundColor);

    //futur develloper border function

    // Draw the segments of the pie chart
    int black = gdImageColorAllocate(img, 0, 0, 0);  // Noir pour les bordures
    draw_segment_and_label(img, segments, segments_count, WIDTH / 2, HEIGHT / 2, 0, MIN(WIDTH, HEIGHT) / 3, black);
    // Draw labels for the segments
    // draw_label(img, segments, segments_count, WIDTH / 2, HEIGHT / 2, 0, MIN(WIDTH, HEIGHT) / 3, black);

    // Drawn the title
    draw_title(img, title, WIDTH / 2, HEIGHT / 10, black);

    return img;
}

void PieChartGenerator::calculate_coordinates(int x, int y, int radius, int angle, int* coord_x, int* coord_y)
{
    *coord_x = x + radius * cos(angle * M_PI / 180);
    *coord_y = y + radius * sin(angle * M_PI / 180);
}

void PieChartGenerator::draw_segment_and_label(gdImagePtr img, PieChartSegment* segments, int length, int x, int y, double start_angle, int radius, int black)
{
    const char* fontPath = FONT_PATH;
    double fontSize = radius * 0.05;
    const int PADDING = 10;

    for (int i = 0; i < length; i++) {
        // Draw segment
        int x_end, y_end;
        double end_angle = start_angle + (segments[i].percentage * 360) / 100;
        // appeller la methode generate_ramdom_color de la structure Color
        Color randColor = generate_random_color();
        int pieColor = gdImageColorAllocate(img, randColor.r, randColor.g, randColor.b);
        gdImageFilledArc(img, x, y, 2 * radius, 2 * radius, start_angle, end_angle, pieColor, gdPie);
        gdImageArc(img, x, y, 2 * radius, 2 * radius, start_angle, end_angle, black);
        calculate_coordinates(x, y, radius, end_angle, &x_end, &y_end);
        gdImageLine(img, x, y, x_end, y_end, black);
        // Draw label
        if (segments[i].percentage >= 1.0)
        {
            double median = (end_angle + start_angle) / 2.0;
            int label_x, label_y;
            calculate_coordinates(x, y, radius * 1.15, median, &label_x, &label_y);

            int brect[8];
            gdImageStringFT(NULL, brect, black, fontPath, fontSize, 0, 0, 0, (char*)segments[i].label.c_str());

            int text_width = brect[2] - brect[0];
            int text_height = brect[3] - brect[5];
            label_x -= text_width / 2;
            label_y += text_height / 2;

            gdImageStringFT(img, brect, black, fontPath, fontSize, 0, label_x, label_y, (char*)segments[i].label.c_str());

            // Draw rectangle around the label
            gdImageRectangle(img, brect[0] - PADDING, brect[5] - PADDING, brect[2] + PADDING, brect[3] + PADDING, black);

            // Calcul du point sur le bord du cercle
            int x_border, y_border;
            calculate_coordinates(x, y, radius, median, &x_border, &y_border);
            // Calcul d'un point intermédiaire sur la médiane
            double median_rad = median * M_PI / 180;
            double mid_radius = 1.05 * radius; // Vous pouvez ajuster cette valeur
            int x_med = x + mid_radius * cos(median_rad);
            int y_med = y + mid_radius * sin(median_rad);
            
            // Dessinez la ligne du bord du cercle au point intermédiaire
            gdImageLine(img, x_border, y_border, x_med, y_med, black);
        }

        start_angle = end_angle;
    }
}


void PieChartGenerator::draw_title(gdImagePtr img, const char* title, int x, int y, int color) {
    int brect[8];
    double size = SIZE_TITLE;
    char* err;
    double angle = 0.0;
    int len = strlen(title);
    char string[len + 1];
    for (int i = 0; i < len; i++)
    {
        string[i] = toupper(title[i]);
    }
    string[len] = '\0';

    err = gdImageStringFT(NULL, &brect[0], color, FONT_PATH, size, angle, 0, 0, string);
    if (err)
    {
        fprintf(stderr, "Impossible de rendre le titre: %s\n", err);
        return;
    }

    gdImageStringFT(img, &brect[0], color, FONT_PATH, size, angle, x - brect[2] / 2, y - 100, string);
}

void PieChartGenerator::saveImage(gdImagePtr img, const std::string& filename) {
    FILE* fp = fopen(filename.c_str(), "wb+");
    if (!fp) {
        perror("Error opening output file for writing");
        return; // Retourne void, ou vous pouvez gérer cette erreur comme vous le souhaitez
    }
    gdImagePng(img, fp);
    fclose(fp);
    gdImageDestroy(img);
}
