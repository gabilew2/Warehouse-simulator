/**
 * @file StorageTest.cpp
 * @brief Source file of tests for the Storage class.
 */

#include <gtest/gtest.h>
#include "Storage/Storage.h"

/**
 * @brief Test to ensure that a Storage object can be instantiated.
 */
TEST(StorageTest, itLives)
{
    Storage(0);
}

/**
 * @brief Test to verify that a new Storage is EMPTY when initialized with zero capacity.
 */
TEST(StorageTest, checkCapacityShouldReturnEmpty)
{
    Storage storage(0);
    EXPECT_EQ(storage.checkCapacity(100), EMPTY);
}

/**
 * @brief Test to verify that Storage is AVAILABLE when initialized with capacity less than total capacity.
 */
TEST(StorageTest, checkCapacityShouldReturnAvailable)
{
    Storage storage(10);
    EXPECT_EQ(storage.checkCapacity(100), AVAILABLE);
}

/**
 * @brief Test to verify that Storage is FULLY when initialized with capacity equal to or greater than total capacity.
 */
TEST(StorageTest, checkCapacityShouldReturnFully)
{
    Storage storage(100);
    EXPECT_EQ(storage.checkCapacity(100), FULLY);

    Storage storage2(150);
    EXPECT_EQ(storage2.checkCapacity(100), FULLY);
}
