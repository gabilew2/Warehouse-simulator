#include <gtest/gtest.h>
#include "SalesReport/SalesReport.h"
#include <QDateTime>

/**
 * @brief Test case to ensure that a SalesReport object can be instantiated.
 */
TEST(SalesReportTest, itLives)
{
    QDateTime time = QDateTime::currentDateTime();
    QList<Report::ProductReport> productList;
    double operationalCosts = 5000.0;
    double netProfit = 10000.0;
    int salesId = 1;

    SalesReport salesReport(salesId, time, productList, operationalCosts, netProfit);
}

/**
 * @brief Test case to verify that the generateReport method returns the correct report format.
 */
TEST(SalesReportTest, generateReportShouldReturnCorrectValue)
{
    QDateTime time = QDateTime::currentDateTime();
    QList<Report::ProductReport> productList =
    {
        {"Product1", 10.0, 5},
        {"Product2", 20.0, 3}
    };

    double operationalCosts = 5000.0;
    double netProfit = 10000.0;
    int salesId = 1;

    SalesReport report(salesId, time, productList, operationalCosts, netProfit);
    QString generatedReport = report.generateReport();

    ASSERT_TRUE(generatedReport.contains(QString("Sales ID: %1").arg(salesId)));
    ASSERT_TRUE(generatedReport.contains(QString("Time: %1").arg(time.toString())));
}
