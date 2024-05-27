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
    QString report = "";
    report += QString("Sales ID: %1\nTime: %2\n")
                  .arg(SalesId)
                  .arg(time.toString());

    report += "Sold Products:\n";

    QFile configFile("settings.sim");
    if(!configFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        report += "Cannot open config file.\n";
        return report;
    }

    QTextStream in(&configFile);
    QString line;
    QMap<QString, int> initialQuantities;

    while(!in.atEnd())
    {
        line = in.readLine();
        if(line.contains("Add product;"))
        {
            QString productName = in.readLine().trimmed();
            in.readLine();
            int quantity = in.readLine().toInt();
            initialQuantities[productName] = quantity;
        }
    }

    for(ProductReport product : productList)
    {
        int initialQuantity = initialQuantities.value(product.name, 0);
        int soldQuantity = initialQuantity - product.quantity;

        operationalCosts += product.price * initialQuantity;

        if(soldQuantity == 0)
        {
            break;
        }

        report += QString("Name: %1, Price: %2, Quantity Sold: %3\n")
                      .arg(product.name)
                      .arg(product.price)
                      .arg(soldQuantity);

        netProfit += product.price * soldQuantity;
    }

    netProfit -= operationalCosts;

    report += "********************\n";
    report += Report::generateReport();

    configFile.close();
    return report;
}
