/**
 * @file Simulation.h
 * @brief Header file for the Simulation class.
 *
 * Declares the Simulation class and its members, which are responsible for managing the overall department store simulation.
 */

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

public:
    /**
     * @brief Construct a new Simulation object.
     *
     * Sets up the initial state of the simulation, including loading settings and preparing the environment.
     */
    Simulation();

    /**
     * @brief Conducts a simulation cycle, processing events for the current cycle.
     *
     * Processes events and updates the simulation state for each cycle.
     * @return Status of the cycle (success or failure).
     */
    status conductCycle();

    /**
     * @brief Responds to a specific event.
     *
     * Handles the given event based on its type and updates the simulation state accordingly.
     * @param event The event to handle.
     * @return Status of event handling (success or failure).
     */
    status respondToEvent(Event& event);

    /**
     * @brief Initiates the simulation by running the main loop.
     *
     * Starts the simulation loop, generating cycles, processing events, and generating reports.
     */
    void run();

    /**
     * @brief Processes all scheduled events.
     *
     * Invokes conductCycle to process events for the current cycle.
     * @return Status of proccessing events).
     */
    status processEvents();

    /**
     * @brief Generates a report summarizing simulation results.
     *
     * Compiles data from the simulation into a formatted report string.
     * @return QString A summary report of the simulation results.
     */
    QString generateReport();
};

#endif
