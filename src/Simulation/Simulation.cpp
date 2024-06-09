/**
 * @file Simulation.cpp
 * @brief Source file for the Simulation class.
 */

#include "Simulation.h"

/**
 * @brief Construct a new Simulation object.
 */
Simulation::Simulation()
{
    std::cout << "Preparing simulation" << std::endl;

    currentTime = QDateTime::currentDateTime();

    QFile settings("settings.csv");

    QFile::rename("SimulationReport.csv", "SimulationReportOld.csv");
    QFile::remove("SimulationReport.csv");

    if(!settings.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        std::cerr << "Error: Can't open settings file." << std::endl;
        return;
    }
    QTextStream in(&settings);

    seed = 100;
    int productIdCounter = 1;

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
            productIdCounter = 1;
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
            int productId = productIdCounter++;

            if(selectWarehouse.addProduct(name, price, quantity, productId) == SUCCESS)
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
            this -> seed = QRandomGenerator::global() -> generate()/readSeed;
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
    std::cout << "Running simulation with " << currentCycle << " cycles." << std::endl;

    if(Warehouses.isEmpty())
    {
        std::cout << "Incorrect settings" << std::endl;
        exit(1);
    }

    std::cout << "Generating cycles." << std::endl;

    int cycles = currentCycle;

    while(currentCycle > 0)
    {
        std::cout << "Processing cycle " << cycles - currentCycle << "." << std::endl;
        int minProductsAvailable = std::numeric_limits<int>::max();
        int totalProducts = 0;

        for (Warehouse& warehouse : Warehouses)
        {
            const QList<Product>& productList = warehouse.getProductList();
            if (productList.isEmpty())
            {
                std::cout << "Warning: No products available in warehouse at " << warehouse.getLocation().toStdString() << std::endl;
                continue;
            }

            int numberOfEvents = QRandomGenerator::global()->bounded(productList.size()) + 1;

            std::cout << "Number of sale events to be generated for warehouse at " << warehouse.getLocation().toStdString() << ": " << numberOfEvents << std::endl;

            for (int event = 0; event < numberOfEvents; ++event)
            {
                events.append(Event::generateEvent("Sell product", seed));
                std::cout << "\033[33mInfo: Generating event - Sell product\033[0m" << std::endl;
            }
        }

        if (events.isEmpty())
        {
            std::cout << "No events generated in this cycle." << std::endl;
        }
        else
        {
            QList<Warehouse> restoreWarehouse = Warehouses;

            if (processEvents() == ERROR && currentCycle != cycles)
            {
                Warehouses = restoreWarehouse;
            }

            QString cycleReport = generateReport();
            std::cout << cycleReport.toStdString() << std::endl;
            events.clear();
        }

        std::cout << "Cycle " << cycles - currentCycle << " completed." << std::endl;
        currentCycle--;
    }
    std::cout << "Simulation completed." << std::endl;
}


/**
 * @brief Processes all scheduled events.
 */
status Simulation::processEvents()
{
    if(conductCycle() == ERROR)
    {
        std::cout << "Error while processing cycle" << std::endl;
        return ERROR;
    }
    return SUCCESS;
}

/**
 * @brief Conducts a simulation cycle, processing events for the current cycle.
 */
status Simulation::conductCycle()
{
    qint64 deltaTime = 0;

    int successEvents = 0;

    for(Event& event : events)
    {
        if(respondToEvent(event) == ERROR)
        {
            std::cout << "Error while processing event." << std::endl;
        }
        else
        {
            successEvents++;
        }

        QDateTime Time = event.getTime();

        if(Time.msecsTo(currentTime) > deltaTime)
        {
            deltaTime = Time.msecsTo(currentTime);
        }
    }

    if(successEvents == 0)
    {
        return ERROR;
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
    int warehouseId = QRandomGenerator::global() -> bounded(Warehouses.size());
    Warehouse& warehouse = Warehouses[warehouseId];

    if(event.getEventType() == "Sell product")
    {
        try
        {
            const QList<Product>& productList = warehouse.getProductList();
            if (productList.isEmpty())
            {
                std::cerr << "ERROR: No products to sell." << std::endl;
                return ERROR;
            }

            int productId = QRandomGenerator::global()->bounded(productList.size()) + productList.begin()->productId;
            std::cout << "Attempting to sell" << productId;
            status result = warehouse.sell(1, productId);

            if (result == ERROR)
            {
                std::cout << "ERROR: Unable to sell product. Product doesn't exists." << std::endl;
                return ERROR;
            }
        }
        catch (const std::exception& e)
        {
            std::cerr << "General Exception caught: " << e.what() << std::endl;
            return ERROR;
        }
    }
    else if (event.getEventType() == "Add product")
    {
        try
        {
            const QList<Product>& productList = warehouse.getProductList();
            int productId = QRandomGenerator::global()->bounded(productList.size());
            const Product& product = productList[productId];

            status result;

            while(warehouse.checkStatus() != FULLY)
            {
                result = warehouse.changeQuantity(product.getQuantity() + 1, productId);
            }

            if (result == ERROR)
            {
                std::cerr << "ERROR: Unable to add product quantity." << std::endl;
                return ERROR;
            }
        }
        catch (const std::exception& e)
        {
            std::cerr << "General Exception caught: " << e.what() << std::endl;
            return ERROR;
        }
    }
    else if (event.getEventType() == "Transfer product")
    {
        try
        {
            const QList<Product>& productList = warehouse.getProductList();
            int productId = QRandomGenerator::global()->bounded(productList.size());
            const Product& productToTransfer = productList[productId];

            auto targetWarehouseIt = Warehouses.end();
            for (auto it = Warehouses.begin(); it != Warehouses.end(); ++it)
            {
                if (it->getLocation() != warehouse.getLocation() && it-> checkStatus() == FULLY)
                {
                    targetWarehouseIt = it;
                    break;
                }
            }

            if (targetWarehouseIt != Warehouses.end())
            {
                Warehouse& targetWarehouse = *targetWarehouseIt;
                int transferQuantity = productToTransfer.getQuantity();
                warehouse.changeQuantity(warehouse.getQuantity(productId) - transferQuantity, productId);
                targetWarehouse.changeQuantity(targetWarehouse.getQuantity(productId) + transferQuantity, productId);
            }
            else
            {
                std::cerr << "ERROR: No target warehouse found for product transfer." << std::endl;
                return ERROR;
            }
        }
        catch (const std::exception& e)
        {
            std::cerr << "General Exception caught: " << e.what() << std::endl;
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
    QString csvReport;
    int id = 0;

    std::cout << "Generating report" << std::endl;

    for(Warehouse& warehouse : Warehouses)
    {
        QList<Report::ProductReport> productNames;
        double featureOperationalCosts = 0;
        for(const Product& product : warehouse.getProductList())
        {
            Report::ProductReport productReport;
            productReport.name = product.getName();
            productReport.price = product.getPrice();
            productReport.quantity = product.getQuantity();

            featureOperationalCosts += productReport.price + productReport.quantity;

            productNames.append(productReport);
        }

        static int salesId = 0;

        WarehouseReport warehouseReport(id++, warehouse.getCurrentCapacity(), productNames, Report::getOperationalCosts(), Report::getNetProfit());
        SalesReport salesReport(salesId++, currentTime, productNames, Report::getOperationalCosts(), Report::getNetProfit());

        Report::setOperationalCosts(Report::getOperationalCosts()+featureOperationalCosts);

        csvReport.append(warehouseReport.generateReport());
        csvReport.append(salesReport.generateReport());
    }

    // Save the CSV report to a file
    QFile csvFile("SimulationReport.csv");

    if(csvFile.open(QIODevice::Append | QIODevice::Text))
    {
        QTextStream out(&csvFile);
        out << "\n";
        out << csvReport;
        csvFile.close();
    }
    else
    {
        std::cerr << "Error while trying to write the CSV report to file." << std::endl;
    }

    return csvReport;
}
