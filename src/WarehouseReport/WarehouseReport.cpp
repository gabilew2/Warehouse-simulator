#include "WarehouseReport.h"

/**
 * @brief Construct a new WarehouseReport object.
 */
WarehouseReport::WarehouseReport(int warehouseId, double capacity, QList<Product*> productList, double operationalCosts, double netProfit) : Report(operationalCosts, netProfit)
{
    this -> warehouseId = warehouseId;
    this -> capacity = capacity;
    this -> productList = productList;
}

/**
 * @brief Generates a detailed warehouse inventory report.
 */
QString WarehouseReport::generateReport()
{
    return Report::generateReport();
}
