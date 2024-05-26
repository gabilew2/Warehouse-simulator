#include "SalesReport.h"

/**
 * @brief Construct a new SalesReport object.
 */
SalesReport::SalesReport(int SalesId, QDateTime time, QList<Product*> productList, double operationalCosts, double netProfit) : Report(operationalCosts, netProfit)
{
    this -> SalesId = SalesId;
    this -> time = time;
    this -> productList = productList;
}

/**
 * @brief Generates a detailed sales report.
 */
QString SalesReport::generateReport()
{
    return Report::generateReport();
}
