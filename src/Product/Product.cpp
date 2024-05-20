#include "Product.h"

/** Static variable initialization. */
int Product::productId = 0;

/**
 * @brief Construct a new Product object.
 */
Product::Product(QString name, double price, int quantity)
{
    ++productId;

    this -> name = name;

    if(price < 0)
    {
        this -> price = 0;
    }
    else
    {
        this -> price = price;
    }

    if(quantity < 0)
    {
        this -> quantity = 0;
    }
    else
    {
        this -> quantity = quantity;
    }
}

/**
 * @brief Sell a quantity of the product.
 */
status Product::sell(int quantityToSell)
{
    if(quantityToSell <= quantity && quantityToSell >= 0)
    {
        quantity -= quantityToSell;
        return SUCCESS;
    }
    else
    {
        return ERROR;
    }
}

/**
 * @brief Update the price of the product.
 */
status Product::updatePrice(double newPrice)
{
    if(newPrice > 0)
    {
        price = newPrice;
        return SUCCESS;
    }
    else
    {
        return ERROR;
    }
}

/**
 * @brief Change the quantity of the product.
 */
status Product::changeQuantity(int quantity)
{
    if(quantity >= 0)
    {
        this -> quantity = quantity;
        return SUCCESS;
    }
    else
    {
        return ERROR;
    }
}

void Product::resetProductId()
{
    productId = 0;
}

// Getters implementation

QString Product::getName()
{
    return name;
}

double Product::getPrice()
{
    return price;
}

int Product::getQuantity()
{
    return quantity;
}
