#ifndef WAREHOUSEREPORT_H
#define WAREHOUSEREPORT_H

#include <Warehouse/Warehouse.h>
#include <Report/Report.h>
#include <QList>

class WarehouseReport : Report
{
private:
    int warehouseId;
    double capacity;
    QList<Product> productList;
public:
    QString generateReport();
};

#endif
