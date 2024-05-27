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
private:
    double capacity;    ///< Storage fill level.
    friend class Warehouse; ///< Grants Warehouse access to private members of Storage.
public:
    /**
     * @brief Construct a new Storage object with a specified capacity.
     *
     * @param initialCapacity The initial capacity of the storage.
     */
    Storage(double capacity);

    /**
     * @brief Check the current capacity status of the storage.
     *
     * @return storageStatus The status of the storage: EMPTY, AVAILABLE, or FULLY.
     */
    storageStatus checkCapacity();
};

#endif
