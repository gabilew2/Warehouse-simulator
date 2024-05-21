#ifndef WAREHOUSE_H
#define WAREHOUSE_H

#include "Storage/Storage.h"
#include "Product/Product.h"
#include <QList>

/**
 * @class Warehouse
 * @brief The Warehouse class represents a warehouse with storage capacity.
 *
 * This class inherits from Storage and provides additional functionality
 * specific to warehouse operations.
 */
class Warehouse : Storage
{
private:
    QString location;   ///< Location of the warehouse.
    QList<Product> productList;     ///< List of products stored in the warehouse.
    double warehouseCapacity;   ///< The total capacity of the storage.
public:
    /**
     * @brief Construct a new Warehouse object.
     *
     * @param location The location of the warehouse.
     * @param warehouseCapacity The initial capacity of the warehouse.
     */
    Warehouse(QString location, double warehouseCapacity);

    static int warehouseId;    ///< Unique identifier for the warehouse.

    /**
     * @brief Check the current status of the warehouse and updates the capacity
     * attribute inherited from the Storage class.
     *
     * @return storageStatus The status of the warehouse: EMPTY, AVAILABLE, or FULL.
     */
    storageStatus checkStatus();

    /**
     * @brief Update the storage capacity of the warehouse.
     *
     * @param newCapacity The new capacity of the warehouse.
     * @return status SUCCESS if the operation is successful, ERROR otherwise.
     */
    status updateStatus(double newCapacity);

    // Product operations

    /**
     * @brief Add a new product to the warehouse.
     *
     * @param name The name of the product.
     * @param price The price of the product.
     * @param quantity The quantity of the product.
     * @return status SUCCESS if the product is added, ERROR otherwise.
     */
    status addProduct(QString name, double price, int quantity);

    /**
     * @brief Update the price of a product in the warehouse.
     *
     * @param newPrice The new price of the product.
     * @param productId The ID of the product.
     * @return status SUCCESS if the price is updated, ERROR otherwise.
     */
    status updatePrice(double newPrice, int productId);

    /**
     * @brief Change the quantity of a product in the warehouse.
     *
     * @param quantity The new quantity of the product.
     * @param productId The ID of the product.
     * @return status SUCCESS if the quantity is updated, ERROR otherwise.
     */
    status changeQuantity(int quantity, int productId);

    /**
     * @brief Sell a quantity of a product from the warehouse.
     *
     * @param quantityToSell The quantity of the product to sell.
     * @param productId The ID of the product.
     * @return status SUCCESS if the product is sold, ERROR otherwise.
     */
    status sell(int quantityToSell, int productId);

    /**
     * @brief Get the name of a product by its ID.
     *
     * @param productId The ID of the product.
     * @return QString The name of the product.
     */
    QString getName(int productId);

    /**
     * @brief Get the price of a product by its ID.
     *
     * @param productId The ID of the product.
     * @return double The price of the product.
     */
    double getPrice(int productId);

    /**
     * @brief Get the quantity of a product by its ID.
     *
     * @param productId The ID of the product.
     * @return int The quantity of the product.
     */
    int getQuantity(int productId);



    //Getters
    QString getLocation();      ///< Get the location of the warehouse.
    QList<Product> getProductList();     ///< Get the list of the products.
    double getCurrentCapacity();         ///< Get the capacity of the warehouse.
};

#endif
