/**
 * @file Storage.h
 * @brief Header file of the Storage class.
 */

#ifndef STORAGE_H
#define STORAGE_H

/** Enum representing the status of the Storage capacity. */
enum storageStatus {EMPTY, AVAILABLE, FULLY};

/**
 * @class Storage
 * @brief The Storage class represents a storage unit with a certain capacity.
 *
 * This class provides a method to check the current status of the storage
 * based on its capacity.
 */
class Storage
{
protected:
    int capacity;    ///< Storage fill level.
public:
    /**
     * @brief Construct a new Storage object with a specified capacity.
     *
     * @param capacity The initial capacity of the storage.
     */
    Storage(int capacity);

    /**
     * @brief Check the current capacity status of the storage.
     *
     * @param totalCapacity The maximum capacity of the storage.
     * @return storageStatus The status of the storage: EMPTY, AVAILABLE, or FULLY.
     */
    storageStatus checkCapacity(int totalCapacity) const;
};

#endif
