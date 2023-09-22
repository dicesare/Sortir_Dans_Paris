/**
 * @file GraphicsUtils.h
 * @author Antony Coco (antony.coco.pro@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-09-22
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef GRAPHICS_UTILS_H
#define GRAPHICS_UTILS_H

#include <string>
#include <random>

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


#endif // GRAPHICS_UTILS_H