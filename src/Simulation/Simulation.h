#ifndef SIMULATION_H
#define SIMULATION_H

#include <Warehouse/Warehouse.h>
#include <WarehouseReport/WarehouseReport.h>
#include <SalesReport/SalesReport.h>
#include <Event/Event.h>
#include <QList>
#include <QDateTime>

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
    QList<Event> events; ///< List of scheduled events.
    QDateTime currentTime; ///< Current simulation time.
    QString eventAgenda; ///< Description of event schedule.
    QList<Warehouse> Warehouses; ///< List of warehouse objects.

public:
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
    status respondToEvent(const Event& event);

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
