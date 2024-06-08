/**
 * @file Product.h
 * @brief Header file for the Product class.
 */

#ifndef PRODUCT_H
#define PRODUCT_H

#include <QString>

/** Enum representing the status of operations on Product. */
enum status {SUCCESS, ERROR};

/**
 * @class Product
 * @brief The Product class represents a product with a name, price, and quantity.
 *
 * This class provides methods to sell the product, update its price, and change its quantity.
 */
class Product
{
private:
    QString name;   ///< Name of the product.
    double price;   ///< Price of the product.
    int quantity;   ///< Quantity of the product in stock.
public:
    int productId;  ///< ID of the product.

    /**
     * @brief Construct a new Product object.
     *
     * @param productId ID of the product.
     * @param name Name of the product.
     * @param price Price of the product. If negative, it will be set to 0.
     * @param quantity Quantity of the product. If negative, it will be set to 0.
     */
    Product(int productId, QString name, double price, int quantity);

    /**
     * @brief Sell a quantity of the product.
     *
     * @param quantityToSell The quantity of the product to sell.
     * @return status SUCCESS if the operation is successful, ERROR otherwise.
     */
    status sell(int quantityToSell);

    /**
     * @brief Update the price of the product.
     *
     * @param newPrice The new price of the product. Must be positive.
     * @return status SUCCESS if the operation is successful, ERROR otherwise.
     */
    status updatePrice(double newPrice);

    /**
     * @brief Change the quantity of the product.
     *
     * @param quantity The new quantity of the product. Must be non-negative.
     * @return status SUCCESS if the operation is successful, ERROR otherwise.
     */
    status changeQuantity(int quantity);

    // Getters
    QString getName() const;  ///< Get the name of the product.
    double getPrice() const;  ///< Get the price of the product.
    int getQuantity() const;  ///< Get the quantity of the product.
};

#endif // PRODUCT_H
