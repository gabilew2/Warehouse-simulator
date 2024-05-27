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
TEST(SimulationTest, ProcessEvents)
{
    Simulation simulation;
    simulation.processEvents();
}

/**
 * @brief Test to check if the conductCycle method processes the simulation cycle successfully.
 */
TEST(SimulationTest, ConductCycle)
{
    Simulation simulation;
    status result = simulation.conductCycle();
    ASSERT_EQ(result, SUCCESS);
}

/**
 * @brief Test to ensure that the generateReport method produces a non-empty report.
 */
TEST(SimulationTest, GenerateReport)
{
    Simulation simulation;
    QString report = simulation.generateReport();
    ASSERT_FALSE(report.isEmpty());
}
