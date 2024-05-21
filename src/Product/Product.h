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

    /**
     * @brief Construct a new Product object.
     *
     * @param name Name of the product.
     * @param price Price of the product. If negative, it will be set to 0.
     * @param quantity Quantity of the product. If negative, it will be set to 0.
     */
    Product(QString name, double price, int quantity);

    static int productId;   ///< Variable to keep track of product ID.

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

    /**
     * @brief Reset the product ID.
     *
     * This static method resets the static product ID to 0. It is useful for testing purposes
     * to ensure that each test starts with a clean slate of product IDs.
     */
    static void resetProductId();

    // Getters
    QString getName();  ///< Get the name of the product.
    double getPrice();  ///< Get the price of the product.
    int getQuantity();  ///< Get the quantity of the product.
};

#endif
