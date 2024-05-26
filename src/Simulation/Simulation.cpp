#include "Simulation.h"

/**
 * @brief Construct a new Simulation object.
 */
Simulation::Simulation()
{
    std::cout << "Preparing simulation" << std::endl;

    currentTime = QDateTime::currentDateTime();

    QFile settings("settings.sim");
    if(!settings.open(QIODevice::ReadOnly | QIODevice::Text)) return;
    QTextStream in(&settings);

    while(!in.atEnd())
    {
        QString line = in.readLine();

        if(line.contains("Add warehouse;"))
        {
            std::cout << "Adding warehouse." << std::endl;
            QString location = in.readLine();
            double capacity = in.readLine().toDouble();
            Warehouses.append(Warehouse(location, capacity));
        }
        else if(line.contains("Add product;"))
        {
            std::cout << "Adding product: ";
            Warehouse& selectWarehouse = Warehouses.last();
            QString name = in.readLine();
            double price = in.readLine().toDouble();
            int quantity = in.readLine().toInt();
            std::cout << selectWarehouse.addProduct(name, price, quantity) << std::endl;
        }
        else if(line.contains("Set currentCycle;"))
        {
            std::cout << "Setting currentCycle: ";
            int currentCycle = in.readLine().toInt();
            this -> currentCycle = currentCycle;
            std::cout << currentCycle << std::endl;
        }
    }

    settings.close();

}

/**
 * @brief Initiates the simulation by running the main loop.
 */
void Simulation::run()
{
    std::cout << "Running simulation." << std::endl;

    QString report;

    if(Warehouses.isEmpty())
    {
        std::cout << "Incorrect settings" << std::endl;
        exit(1);
    }

    while(currentCycle > 0)
    {
        int numberOfEvents = QRandomGenerator::global()->generate();
        for(numberOfEvents; numberOfEvents > 0; --numberOfEvents)
        {
            events.append(Event::generateEvent("Sell product"));
        }

        processEvents();

        QString cycleReport = generateReport();
        report.append(cycleReport);
        std::cout << cycleReport.toStdString() << std::endl;
    }

    std::cout << report.toStdString() << std::endl;

}

/**
 * @brief Processes all scheduled events.
 */
void Simulation::processEvents()
{
    if(conductCycle() == ERROR)
    {
        std::cout << "Error while processing cycle" << std::endl;
    }

    currentCycle--;
}

/**
 * @brief Conducts a simulation cycle, processing events for the current cycle.
 */
status Simulation::conductCycle()
{
    qint64 deltaTime = 0;

    for(Event& event : events)
    {
        if(!respondToEvent(event))
        {
            std::cout << "Error while processing event." << std::endl;
            return ERROR;
        }

        QDateTime Time = event.getTime();

        if(Time.msecsTo(currentTime) > deltaTime)
        {
            deltaTime = Time.msecsTo(currentTime);
        }
    }

    events.clear();
    currentTime = currentTime.addSecs(deltaTime);
    return SUCCESS;
}

/**
 * @brief Responds to a specific event.
 */
status Simulation::respondToEvent(Event& event)
{
    int productId = QRandomGenerator::global()->bounded(1000);
    int warehouseId = QRandomGenerator::global()->bounded(10);

    if(event.getEventType() == "Sell product")
    {
        try
        {
            Warehouse& warehouse = Warehouses[warehouseId];
            status result = warehouse.sell(1,productId);
            if(result == ERROR)
            {
                return ERROR;
            }
        }
        catch (...)
        {
            return ERROR;
        }

    }
    return SUCCESS;
}

/**
 * @brief Generates a report summarizing simulation results.
 */
QString Simulation::generateReport()
{
    QString report;

    for(Warehouse& warehouse : Warehouses)
    {
        QList<Product> productList = warehouse.getProductList();
        QList<Product*> productPointerList;
        for (Product& product : productList)
        {
            productPointerList.append(&product);
        }

        WarehouseReport warehouseReport = WarehouseReport(warehouse.warehouseId, warehouse.getCurrentCapacity(), productPointerList, 0, 0);
        report.append(warehouseReport.generateReport());
        SalesReport salesReport = SalesReport(warehouse.warehouseId, currentTime, productPointerList, 0, 0);
        report.append(salesReport.generateReport());
    }

    return report;

}
