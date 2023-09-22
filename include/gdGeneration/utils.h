/**
 * @file utils.h
 * @author Antony Coco (antony.coco.pro@gmail.com)
 * @brief Provides utility macros and definitions.
 * @version 0.1
 * @date 2023-09-22
 * @copyright Copyright (c) 2023
 * 
 * This header defines utility macros and functions that can be reused 
 * across different parts of the project.
 */
#ifndef UTILS_H
#define UTILS_H

#ifndef MIN
/**
 * @brief Macro to determine the minimum of two values.
 * 
 * @param a First value.
 * @param b Second value.
 * @return The lesser value between a and b.
 */
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#endif

#endif // UTILS_H
