#ifndef WAREHOUSE_H
#define WAREHOUSE_H

#include <Storage/Storage.h>
#include <Product/Product.h>
#include <QList>

class Warehouse : Storage
{
private:
    QString location;
    double capacity;
    QList<Product> productList;
public:
    int warehouseId;
    status checkStatus();
    status updateStatus(double newCapacity);
};

#endif
