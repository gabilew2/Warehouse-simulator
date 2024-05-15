#ifndef SALESREPORT_H
#define SALESREPORT_H

#include <Report/Report.h>
#include <QDateTime>
#include <QList>
#include <Warehouse/Warehouse.h>

class SalesReport : Report
{
private:
    int SalesId;
    QDateTime time;
    QList<Product> productList;
public:
    QString generateReport();
};

#endif
