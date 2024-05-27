#include "WarehouseReport.h"

/**
 * @brief Construct a new WarehouseReport object.
 */
WarehouseReport::WarehouseReport(int warehouseId, double capacity, QList<ProductReport> productList, double operationalCosts, double netProfit) : Report(operationalCosts, netProfit)
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
    QString report;
    report += QString("Warehouse ID: %1\nCapacity: %2\n")
                  .arg(warehouseId)
                  .arg(capacity);

    report += "Product List:\n";
    for(ProductReport product : productList)
    {
        report += QString("Name: %1, Price: %2, Quantity: %3\n")
                      .arg(product.name)
                      .arg(product.price)
                      .arg(product.quantity);
    }

    return report;
}
