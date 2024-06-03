#include "Simulation.h"

/**
 * @brief Construct a new Simulation object.
 */
Simulation::Simulation()
{
    std::cout << "Preparing simulation" << std::endl;

    currentTime = QDateTime::currentDateTime();

    QFile settings("settings.csv");
    if(!settings.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        std::cerr << "Error: Can't open settings file." << std::endl;
        return;
    }
    QTextStream in(&settings);

    seed = 100;

    while(!in.atEnd())
    {
        QString line = in.readLine();
        QStringList fields = line.split(',');

        if(fields.isEmpty())
        {
            continue;
        }

        if(fields[0] == "Warehouse")
        {
            if(fields.size() < 3)
            {
                std::cerr << "Error: Incomplete warehouse data." << std::endl;
                continue;
            }
            std::cout << "Adding warehouse." << std::endl;
            QString location = fields[1];
            double capacity = fields[2].toDouble();
            Warehouses.append(Warehouse(location, capacity));
        }
        else if(fields[0] == "Product")
        {
            if(fields.size() < 4)
            {
                std::cerr << "Error: Incomplete product data." << std::endl;
                continue;
            }
            std::cout << "Adding product: ";
            Warehouse& selectWarehouse = Warehouses.last();
            QString name = fields[1];
            double price = fields[2].toDouble();
            int quantity = fields[3].toInt();

            if(selectWarehouse.addProduct(name, price, quantity) == SUCCESS)
            {
                std::cout << "SUCCESS" << std::endl;
            }
            else
            {
                std::cerr << "ERROR: Unable to add product." << std::endl;
            }
        }
        else if(fields[0] == "Cycles")
        {
            if(fields.size() < 5)
            {
                std::cerr << "Error: Incomplete cycle data." << std::endl;
                continue;
            }
            std::cout << "Setting currentCycle: ";
            int currentCycle = fields[4].toInt();
            this -> currentCycle = currentCycle;
            std::cout << currentCycle << std::endl;
        }
        else if(fields[0] == "Seed")
        {
            if(fields.size() < 6)
            {
                std::cerr << "Error: Incomplete seed data." << std::endl;
                continue;
            }
            std::cout << "Setting seed: ";
            int readSeed = fields[5].toInt();
            this->seed = readSeed;
            std::cout << readSeed << std::endl;
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

    generateReport();

    std::cout << "Generating cycles." << std::endl;

    while(currentCycle > 0)
    {
        int numberOfEvents = QRandomGenerator::global()->bounded(100);
        for(numberOfEvents; numberOfEvents > 0; --numberOfEvents)
        {
            events.append(Event::generateEvent("Sell product", seed));
        }

        std::cout << "Processing cycle." << std::endl;
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
    int warehouseId = QRandomGenerator::global()->bounded(Warehouses.size());
    int productId = QRandomGenerator::global()->bounded((int)Warehouses[warehouseId].getCurrentCapacity());

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
    QString readableReport;
    QString csvReport;
    int id = 0;

    std::cout << "Generating report" << std::endl;

    // Headers for the CSV report
    csvReport += "Warehouse ID,Capacity,Product Name,Price,Quantity\n";

    for(Warehouse& warehouse : Warehouses)
    {
        readableReport.append(QString("---- Warehouse ID: %1 ----\n").arg(id));
        readableReport.append(QString("Capacity: %1\n").arg(warehouse.getCurrentCapacity()));
        readableReport.append("Product Name | Price | Quantity\n");
        readableReport.append("---------------------------------\n");

        QList<Report::ProductReport> productNames;
        for(Product& product : warehouse.getProductList())
        {
            Report::ProductReport productReport;
            productReport.name = product.getName();
            productReport.price = product.getPrice();
            productReport.quantity = product.getQuantity();

            productNames.append(productReport);

            // Append data to CSV report
            csvReport += QString("%1,%2,%3,%4,%5\n")
                             .arg(id)
                             .arg(warehouse.getCurrentCapacity())
                             .arg(product.getName())
                             .arg(product.getPrice())
                             .arg(product.getQuantity());

            // Append data to readable report
            readableReport.append(QString("%1 | %2 | %3\n")
                                      .arg(product.getName())
                                      .arg(product.getPrice())
                                      .arg(product.getQuantity()));
        }

        readableReport.append("--------------------\n");

        static int salesId = 0;

        WarehouseReport warehouseReport(id++, warehouse.getCurrentCapacity(), productNames, 0, 0);
        readableReport.append(warehouseReport.generateReport());
        readableReport.append("--------------------\n");
        SalesReport salesReport(salesId++, currentTime, productNames, 0, 0);
        readableReport.append(salesReport.generateReport());
        readableReport.append("--------------------\n");
    }

    // Display the readable report on the screen
    std::cout << readableReport.toStdString() << std::endl;

    // Save the CSV report to a file
    QFile csvFile("SimulationReport.csv");

    if(csvFile.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream out(&csvFile);
        out << csvReport;
        csvFile.close();
    }
    else
    {
        std::cerr << "Error while trying to write the CSV report to file." << std::endl;
    }

    return readableReport;
}
