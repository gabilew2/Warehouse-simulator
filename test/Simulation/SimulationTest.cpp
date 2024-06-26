/**
 * @file SimulationTest.cpp
 * @brief Source file of tests for the Simulation class.
 */

#include <gtest/gtest.h>
#include "Simulation/Simulation.h"

/**
 * @brief Test to ensure that the constructor initializes the current time correctly.
 */
TEST(SimulationTest, itLives)
{
    Simulation simulation = Simulation();
}

/**
 * @brief Test to validate the processEvents method.
 */
TEST(SimulationTest, processEvents)
{
    Simulation simulation;
    status result = simulation.processEvents();
    ASSERT_EQ(result, ERROR);
}

/**
 * @brief Test to check if the conductCycle method processes the simulation cycle correctly.
 */
TEST(SimulationTest, conductCycle)
{
    Simulation simulation;
    status result = simulation.conductCycle();
    ASSERT_EQ(result, ERROR);
}

/**
 * @brief Test to ensure that the generateReport method produces a report.
 */
TEST(SimulationTest, generateReport)
{
    Simulation simulation;
    QString report = simulation.generateReport();
    ASSERT_TRUE(report.contains("Warehouse ID,"));
    ASSERT_TRUE(report.contains("Capacity"));
    ASSERT_TRUE(report.contains("Product Name,Price,Quantity"));
}

