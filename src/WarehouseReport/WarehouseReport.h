#ifndef WAREHOUSEREPORT_H
#define WAREHOUSEREPORT_H

#include <Warehouse/Warehouse.h>
#include <Report/Report.h>
#include <QList>

/**
 * @class WarehouseReport
 * @brief The WarehouseReport class extends the Report class to provide a report specifically for warehouse inventory.
 *
 * This class inherits from Report and is responsible for generating a warehouse report,
 * which includes details such as warehouse ID, capacity, and a list of products stored.
 */
class WarehouseReport : Report
{
private:
    int warehouseId; ///< Unique identifier for the warehouse.
    double capacity; ///< Total storage capacity of the warehouse.
    QList<Product> productList; ///< List of products stored in the warehouse.

public:
    /**
     * @brief Generates a detailed warehouse inventory report.
     * @return A formatted string representing the warehouse inventory report.
     */
    QString generateReport();
};

#endif
