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

    QFile configFile("settings.csv");
    if(!configFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        report += "Cannot open config file.\n";
        return report;
    }

    QTextStream in(&configFile);
    QString line;
    QMap<QString, int> initialQuantities;

    // Read the initial quantities from the CSV file.
    while(!in.atEnd())
    {
        line = in.readLine();
        QStringList fields = line.split(',');

        if(fields.isEmpty() || fields[0] != "Product")
        {
            continue;
        }

        QString productName = fields[1].trimmed();
        int quantity = fields[3].toInt();
        initialQuantities[productName] = quantity;
    }

    for(const ProductReport& product : productList)
    {
        int initialQuantity = initialQuantities.value(product.name, 0);
        int soldQuantity = initialQuantity - product.quantity;

        operationalCosts += product.price * initialQuantity;

        if(soldQuantity == 0)
        {
            continue;
        }

        report += QString("%1,%2,%3\n")
                      .arg(product.name)
                      .arg(product.price)
                      .arg(soldQuantity);

        netProfit += product.price * soldQuantity;
    }

    netProfit -= operationalCosts;

    report += Report::generateReport();

    configFile.close();
    return report;
}
