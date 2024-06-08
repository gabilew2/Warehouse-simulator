/**
 * @file SalesReportTest.cpp
 * @brief Source file of tests for the SalesReport class.
 */

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
 * @brief Test case to verify that the SalesReport::generateReport method returns the correct CSV format.
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
    QString generatedCSV = report.generateReport();

    QString expectedCSVStart = QString("Sales ID,Time\n%1,%2\n").arg(salesId).arg(time.toString("yyyy-MM-dd hh:mm:ss"));
    ASSERT_TRUE(generatedCSV.startsWith(expectedCSVStart));
}
