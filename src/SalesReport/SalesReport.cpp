/**
 * @file SalesReport.cpp
 * @brief Source file for the SalesReport class.
 */

#include "SalesReport.h"

/**
 * @brief Construct a new SalesReport object.
 */
SalesReport::SalesReport(int SalesId, QDateTime time, QList<ProductReport> productList, double operationalCosts, double netProfit) : Report(operationalCosts, netProfit)
{
    this -> salesId = SalesId;
    this -> time = time;
    this -> productList = productList;
}

/**
 * @brief Generates a detailed sales report.
 */
QString SalesReport::generateReport() const
{
    QString report;
    report += QString("Sales ID,Time\n%1,%2\n")
                  .arg(salesId)
                  .arg(time.toString("yyyy-MM-dd hh:mm:ss"));

    report += "Product Name,Price,Quantity Sold\n";

    for(const ProductReport& product : productList)
    {
        if(product.quantity > 0)
        {
            report += QString("%1,%2,%3\n")
                          .arg(product.name)
                          .arg(product.price)
                          .arg(product.quantity);

            setNetProfit(getNetProfit() + product.price * product.quantity);
        }
    }

    setNetProfit(getNetProfit()-getOperationalCosts());

    report += Report::generateReport();

    setNetProfit(getNetProfit()+getOperationalCosts());

    return report;
}
