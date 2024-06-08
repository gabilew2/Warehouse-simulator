#ifndef SIMULATION_H
#define SIMULATION_H

#include <Warehouse/Warehouse.h>
#include <WarehouseReport/WarehouseReport.h>
#include <SalesReport/SalesReport.h>
#include <Event/Event.h>
#include <QList>
#include <QDateTime>
#include <QFile>
#include <QRandomGenerator>
#include <iostream>

/**
 * @class Simulation
 * @brief The Simulation class manages the overall department store simulation.
 *
 * This class orchestrates the simulation process, including event handling,
 * warehouse management, product operations, and reporting.
 */
class Simulation
{
private:
    int currentCycle; ///< Current simulation cycle.
    int seed; ///< Random number generator seed.
    QList<Event> events; ///< List of scheduled events.
    QDateTime currentTime; ///< Current simulation time.
    QList<Warehouse> Warehouses; ///< List of warehouse objects.
    QRandomGenerator randomGenerator; ///< Pseudo-random generator for generating random events;

public:
    /**
     * @brief Construct a new Simulation object.
     */
    Simulation();

    /**
     * @brief Conducts a simulation cycle, processing events for the current cycle.
     * @return Status of the cycle (success or failure).
     */
    status conductCycle();

    /**
     * @brief Responds to a specific event.
     * @param event The event to handle.
     * @return Status of event handling (success or failure).
     */
    status respondToEvent(Event& event);

    /**
     * @brief Initiates the simulation by running the main loop.
     */
    void run();

    /**
     * @brief Processes all scheduled events.
     */
    void processEvents();

    /**
     * @brief Generates a report summarizing simulation results.
     * @return A formatted report string.
     */
    QString generateReport();
};

#endif
