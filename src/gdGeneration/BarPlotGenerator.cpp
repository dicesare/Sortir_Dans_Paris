#include "../../include/gdGeneration/BarPlotGenerator.h"
#include "../../include/gdGeneration/GraphicsUtils.h"
#include "BarPlotGenerator.h"

BarPlotGenerator::BarPlotGenerator() : fileHelper() {}
BarPlotGenerator::~BarPlotGenerator() {}

Color BarPlotGenerator::generate_random_color()
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


void BarPlotGenerator::loadDataFromJson (const std::map<std::string, nlohmann::json>& jsonData) {
    for (const auto& [key, event] : jsonData) {
        // Vérifiez que la clé "tags" est présente et est un tableau pour chaque événement
        if (event.is_object() && event.find("tags") != event.end() && event["tags"].is_array()) {
            for (const auto& tag : event["tags"]) {
                if (tag.is_null()) continue;
                std::string tagStr = tag.get<std::string>();
                if (isValidTag(tagStr)) {
                    tagFrequency[tagStr]++;
                }
            }
        }
    }
}

bool BarPlotGenerator::isValidTag(const std::string& tag) {
    for (char c : tag) {
        if (!isalpha(c)) return false;
    }
    return true;
}

void BarPlotGenerator::generateBarPlot(const std::string& outputFilename) {
    const int width = WIDTH;
    const int height = HEIGHT;
    const double fontSize = height * 0.01;
    const double angle = 0.785398;  // 45° en radians
    double titleFontSize = height * 0.04 ;  // Définissez une taille de police appropriée pour le titre
    std::string title = formatTitle(outputFilename);  // Formatage du titre de l'image
    // Initialisation de l'image
    gdImagePtr img = gdImageCreate(width, height);
    int white = gdImageColorAllocate(img, 255, 255, 255);
    int black = gdImageColorAllocate(img, 0, 0, 0);

    // Détermination de la valeur maximale de 'second' dans tagFrequency
    auto maxIt = std::max_element(tagFrequency.begin(), tagFrequency.end(),
                                  [](const auto& a, const auto& b) {
                                      return a.second < b.second;
                                  });
    int maxValue = maxIt->second;

    // Calcul de la largeur de barre en prenant en compte les marges à droite et à gauche
    int effectiveWidth = width * 0.8;  // 80% de la largeur totale après prise en compte des marges de 10% à gauche et à droite
    int barWidth = effectiveWidth / (2 * tagFrequency.size());
    int barHeightProp = height * 0.7 / maxValue;

    int x = width * 0.1 + barWidth;  // Position initiale pour la première barre avec marge de 10%
    const int baseLine = height * 0.9;  // L'axe des abscisses rehaussé de 10%
    const int tickLength = height * 0.01; // longueur du trait vertical de 2 % de la hauteur de l'image
    const int tickWidth = 4; // largeur du trait vertical de 4 pixels
    int brectTitle[8];
    
    gdImageStringFT(NULL, brectTitle, black, FONT_PATH, titleFontSize, 0, 0, 0, title.c_str());
    int titleWidth = brectTitle[2] - brectTitle[0];
    int titleHeight = brectTitle[3] - brectTitle[5];
    int titleX = (width - titleWidth) / 2;
    int titleY = titleHeight + 20; // Donnez une marge de 20 pixels entre le haut de l'image et le titre

    gdImageStringFT(img, brectTitle, black, FONT_PATH, titleFontSize, 0, titleX, titleY, title.c_str());

    for (const auto& bar : tagFrequency) {
        // Couleur aléatoire pour la barre
        Color randColor = generate_random_color();
        int barColor = gdImageColorAllocate(img, randColor.r, randColor.g, randColor.b);

        // Calcul de la hauteur de la barre
        int barHeight = bar.second * barHeightProp;
        
        // Dessin de la barre
        gdImageFilledRectangle(img, x, baseLine - barHeight, x + barWidth, baseLine, barColor);

         // Ajout du petit rectangle sous la barre comme trait vertical "large"
        int tickLeft = x + (barWidth - tickWidth) / 2;
        int tickRight = tickLeft + tickWidth;
        gdImageFilledRectangle(img, tickLeft, baseLine, tickRight, baseLine + tickLength, black);

        // Placement du texte incliné pour le label
        int brect[8];
        gdImageStringFT(NULL, brect, black, FONT_PATH, fontSize, angle, 0, 0, bar.first.c_str());
        int text_width = brect[2] - brect[0];
        int text_height = brect[1] - brect[5];
        gdImageStringFT(img, brect, black, FONT_PATH, fontSize, angle, x + barWidth - text_height, baseLine + text_width * 1.5, bar.first.c_str());

        // Affichage du nombre d'occurrences au-dessus de la barre
        std::string occurrenceStr = std::to_string(bar.second);
        gdImageStringFT(NULL, brect, black, FONT_PATH, fontSize, 0, 0, 0, occurrenceStr.c_str());
        text_width = brect[2] - brect[0];
        gdImageStringFT(img, brect, black, FONT_PATH, fontSize, 0, x + barWidth / 2 - text_width / 2, baseLine - barHeight - 10, occurrenceStr.c_str());

        x += 2 * barWidth;  // Mise à jour de la position x pour la prochaine barre
    }

    // Sauvegarde de l'image
    fileHelper.setSubfolder("resources/graphic");
    std::string output_path = fileHelper.getFilePath(outputFilename);
    saveImage(img, output_path);
}


void BarPlotGenerator::saveImage(gdImagePtr img, const std::string& filename) {
    FILE* fp = fopen(filename.c_str(), "wb+");
    if (!fp) {
        perror("Error opening output file for writing");
        return; // Retourne void, ou vous pouvez gérer cette erreur comme vous le souhaitez
    }
    gdImagePng(img, fp);
    fclose(fp);
    gdImageDestroy(img);
}

std::string BarPlotGenerator::formatTitle(const std::string& filename) {
    // Supprimez l'extension du fichier
    std::string base = filename.substr(0, filename.find_last_of("."));

    // Ne gardez que les lettres et ajoutez un espace entre chaque mot
    std::string cleaned;
    bool lastWasLetter = false;
    for (char c : base) {
        if (std::isalpha(c)) {
            if (lastWasLetter) {
                cleaned += std::tolower(c);
            } else {
                cleaned += std::toupper(c);
                lastWasLetter = true;
            }
        } else {
            cleaned += ' ';
            lastWasLetter = false;
        }
    }

    // Enlevez les espaces éventuels en début ou en fin de chaîne
    cleaned.erase(0, cleaned.find_first_not_of(' ')); // trim start
    cleaned.erase(cleaned.find_last_not_of(' ') + 1); // trim end

    return cleaned;
}

