#include "Storage.h"

/**
 * @brief Construct a new Storage object with a specified capacity.
 */
Storage::Storage(double capacity)
{
    this -> capacity = capacity;
}

/**
 * @brief Check the current capacity status of the storage.
 */
storageStatus Storage::checkCapacity()
{
    if(capacity == 0)
    {
        return EMPTY;
    }
    else if(capacity > 0 && capacity < 1)
    {
        return AVAILABLE;
    }
    else
    {
        return FULLY;
    }
}
