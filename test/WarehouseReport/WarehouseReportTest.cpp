#include <gtest/gtest.h>
#include "WarehouseReport/WarehouseReport.h"
#include <QDateTime>

/**
 * @brief Test case to ensure that a WarehouseReport object can be instantiated.
 */
TEST(WarehouseReportTest, itLives)
{
    int warehouseId = 1;
    double capacity = 1000.0;
    QList<Report::ProductReport> productList;
    double operationalCosts = 2000.0;
    double netProfit = 5000.0;

    WarehouseReport report(warehouseId, capacity, productList, operationalCosts, netProfit);
}

/**
 * @brief Test case to verify that the generateReport method returns the correct report format.
 */
TEST(WarehouseReportTest, generateReportShouldReturnCorrectValue)
{
    int warehouseId = 1;
    double capacity = 1000.0;
    QList<Report::ProductReport> productList =
    {
        {"Product1", 10.0, 5},
        {"Product2", 20.0, 3}
    };

    double operationalCosts = 2000.0;
    double netProfit = 5000.0;

    WarehouseReport report(warehouseId, capacity, productList, operationalCosts, netProfit);
    QString generatedReport = report.generateReport();

    ASSERT_TRUE(generatedReport.contains(QString("Warehouse ID: %1").arg(warehouseId)));
    ASSERT_TRUE(generatedReport.contains(QString("Capacity: %1").arg(capacity)));
}
