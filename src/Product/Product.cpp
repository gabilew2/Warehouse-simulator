#include "Product.h"

/**
 * @brief Construct a new Product object.
 */
Product::Product(int productId, QString name, double price, int quantity)
{
    this -> productId = productId;

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
    if(quantityToSell <= 0)
    {
        return ERROR; // Ensure quantityToSell is positive
    }

    if(quantityToSell <= quantity)
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

// Getters implementation

QString Product::getName() const
{
    return name;
}

double Product::getPrice() const
{
    return price;
}

int Product::getQuantity() const
{
    return quantity;
}

