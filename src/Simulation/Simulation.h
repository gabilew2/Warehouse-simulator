#ifndef SIMULATION_H
#define SIMULATION_H

#include <Warehouse/Warehouse.h>
#include <WarehouseReport/WarehouseReport.h>
#include <SalesReport/SalesReport.h>
#include <Event/Event.h>
#include <QList>
#include <QDateTime>

class Simulation
{
private:
    int currentCycle;
    QList<Event> events;
    QDateTime currentTime;
    QString eventAgenda;
    QList<Warehouse> Warehouses;

public:
    status conductCycle();
    status respondToEvent(const Event& event);
    void run();
    void processEvents();
    QString generateReport();
};

#endif
