#include "SalesReport.h"

/**
 * @brief Construct a new SalesReport object.
 */
SalesReport::SalesReport(int SalesId, QDateTime time, QList<ProductReport> productList, double operationalCosts, double netProfit) : Report(operationalCosts, netProfit)
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
    QString report;
    report += QString("Sales ID,Time\n%1,%2\n")
                  .arg(SalesId)
                  .arg(time.toString("yyyy-MM-dd hh:mm:ss"));

    report += "Product Name,Price,Quantity Sold\n";

    for(const ProductReport& product : productList)
    {
        static int initialQuantity = 0;
        int soldQuantity = abs(initialQuantity - product.quantity);
        initialQuantity = soldQuantity;

        if(soldQuantity <= 0)
        {
            continue;
        }

        report += QString("%1,%2,%3\n")
                      .arg(product.name)
                      .arg(product.price)
                      .arg(soldQuantity);

        setNetProfit(getNetProfit()+product.price * soldQuantity);
    }

    setNetProfit(getNetProfit()-getOperationalCosts());

    report += Report::generateReport();

    setNetProfit(getNetProfit()+getOperationalCosts());

    return report;
}
