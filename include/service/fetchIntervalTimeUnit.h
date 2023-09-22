/**
 * @file fetchIntervalTimeUnit.h
 * @author Antony Coco (antony.coco.pro@gmail.com)
 * @brief Provides utility macros and definitions related to time interval units.
 * @version 0.1
 * @date 2023-09-22
 * @copyright Copyright (c) 2023
 */

#ifndef FETCH_INTERVAL_TIME_UNIT_H
#define FETCH_INTERVAL_TIME_UNIT_H

namespace FetchIntervalTimeUnit {

    /**
     * @brief Enumeration to represent different time interval units.
     * 
     * This enumeration provides different units of time that can be used
     * throughout the application to denote intervals for fetching or any
     * other time-related functionality.
     */
    enum fitu {
        SEC,     ///< Represents seconds.
        MIN,     ///< Represents minutes.
        HR,      ///< Represents hours.
        UNKNOWN  ///< Represents an unknown or unspecified time unit.
    };

}

#endif // FETCH_INTERVAL_TIME_UNIT_H
