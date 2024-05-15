#ifndef PRODUCT_H
#define PRODUCT_H

#include <QString>

enum status {SUCCESS, ERROR};

class Product
{
private:
    QString name;
    double price;
    int quantity;
public:
    int productId;
    status sell(int quantityToSell);
    status updatePrice(double newPrice);
    status changeQuantity(int quantity);
};

#endif
