/**
 * @file Storage.cpp
 * @brief Source file of the Storage class.
 */

#include "Storage.h"

/**
 * @brief Construct a new Storage object with a specified capacity.
 */
Storage::Storage(int capacity)
{
    this -> capacity = capacity;
}

/**
 * @brief Check the current capacity status of the storage.
 */
storageStatus Storage::checkCapacity(int totalCapacity) const
{
    if (capacity == 0)
    {
        return EMPTY;
    }
    else if (capacity > 0 && capacity < totalCapacity)
    {
        return AVAILABLE;
    }
    else
    {
        return FULLY;
    }
}
