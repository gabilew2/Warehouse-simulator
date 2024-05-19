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
    EXPECT_EQ(storage.checkCapacity(), EMPTY);
}

/**
 * @brief Test to verify that Storage is AVAILABLE when initialized with capacity less than 100.
 */
TEST(StorageTest, checkCapacityShouldReturnAvailable)
{
    Storage storage(0.01);
    Storage storage2(0.25);
    Storage storage3(0.50);
    Storage storage4(0.75);
    Storage storage5(0.9999);

    EXPECT_EQ(storage.checkCapacity(), AVAILABLE);
    EXPECT_EQ(storage2.checkCapacity(), AVAILABLE);
    EXPECT_EQ(storage3.checkCapacity(), AVAILABLE);
    EXPECT_EQ(storage4.checkCapacity(), AVAILABLE);
    EXPECT_EQ(storage5.checkCapacity(), AVAILABLE);
}

/**
 * @brief Test to verify that Storage is FULLY when initialized with capacity of 100 or more.
 */
TEST(StorageTest, checkCapacityShouldReturnFully)
{
    Storage storage(100);
    EXPECT_EQ(storage.checkCapacity(), FULLY);
}
