#include "Warehouse.h"

/** Static variable initialization. */
int Warehouse::warehouseId = 0;

/**
 * @brief Construct a new Warehouse object.
 */
Warehouse::Warehouse(QString location, double warehouseCapacity) : Storage(0)
{
    ++warehouseId;
    this->location = location;

    if (warehouseCapacity >= 0)
    {
        this->warehouseCapacity = warehouseCapacity;
    }
    else
    {
        this->warehouseCapacity = 0;
    }
}

/**
 * @brief Check the current status of the warehouse and update the capacity
 * attribute inherited from the Storage class.
 */
storageStatus Warehouse::checkStatus()
{
    if (warehouseCapacity == 0)
    {
        return EMPTY;
    }

    int sumOfProductInstances = 0;

    for (Product& product : productList)
    {
        sumOfProductInstances += product.getQuantity();
    }

    if (sumOfProductInstances == warehouseCapacity)
    {
        return FULLY;
    }

    capacity = sumOfProductInstances;

    return checkCapacity(warehouseCapacity);
}

/**
 * @brief Update the storage capacity of the warehouse.
 */
status Warehouse::updateStatus(int newCapacity)
{
    if (newCapacity < 0)
    {
        return ERROR;
    }

    int sumOfProductInstances = capacity;

    if (newCapacity >= sumOfProductInstances)
    {
        warehouseCapacity = newCapacity;
        capacity = sumOfProductInstances;
        return SUCCESS;
    }
    else
    {
        return ERROR;
    }
}

/**
  * @brief Add a new product to the warehouse.
  */
status Warehouse::addProduct(QString name, double price, int quantity)
{
    int sumOfProductInstances = capacity;

    if(sumOfProductInstances + quantity <= warehouseCapacity && quantity >= 0 && price >= 0)
    {
        productList.append(Product(name, price, quantity));
        capacity += quantity;
        return SUCCESS;
    }
    else
    {
        return ERROR;
    }
}

/**
  * @brief Update the price of a product in the warehouse.
  */
status Warehouse::updatePrice(double newPrice, int productId)
{
    bool productFound = false; ///< Contains false if the product was not found in the productList.

    for(Product& product : productList)
    {
        if(product.productId == productId)
        {
            return product.updatePrice(newPrice);
        }
    }

    if(productFound == false)
    {
        return ERROR;
    }
}

/**
  * @brief Change the quantity of a product in the warehouse.
  */
status Warehouse::changeQuantity(int quantity, int productId)
{
    int sumOfProductInstances = capacity;

    for(Product& product : productList)
    {
        if(product.productId == productId)
        {
            int currentQuantity = product.getQuantity();

            if(sumOfProductInstances - currentQuantity + quantity <= warehouseCapacity)
            {
                status Status = product.changeQuantity(quantity);

                if(Status == SUCCESS)
                {
                    capacity = sumOfProductInstances - currentQuantity + quantity;
                    return SUCCESS;
                }
                else
                {
                    return ERROR;
                }
            }
            else
            {
                return ERROR;
            }
        }
    }
    return ERROR;
}

/**
  * @brief Sell a quantity of a product from the warehouse.
  */
status Warehouse::sell(int quantityToSell, int productId)
{
    bool productFound = false; ///< Contains false if the product was not found in the productList.

    for(Product& product : productList)
    {
        if(product.productId == productId)
        {
            return product.sell(quantityToSell);
        }
    }

    if(productFound == false)
    {
        return ERROR;
    }
}

/**
  * @brief Get the name of a product by its ID.
  */
QString Warehouse::getName(int productId)
{
    bool productFound = false; ///< Contains false if the product was not found in the productList.

    for(Product& product : productList)
    {
        if(product.productId == productId)
        {
            return product.getName();
        }
    }

    if(productFound == false)
    {
        return "ERROR";
    }
}

/**
  * @brief Get the price of a product by its ID.
  */
double Warehouse::getPrice(int productId)
{
    bool productFound = false; ///< Contains false if the product was not found in the productList.

    for(Product& product : productList)
    {
        if(product.productId == productId)
        {
            return product.getPrice();
        }
    }

    if(productFound == false)
    {
        return -1;
    }
}

/**
  * @brief Get the quantity of a product by its ID.
  */
int Warehouse::getQuantity(int productId)
{
    bool productFound = false; ///< Contains false if the product was not found in the productList.

    for(Product& product : productList)
    {
        if(product.productId == productId)
        {
            return product.getQuantity();
        }
    }

    if(productFound == false)
    {
        return -1;
    }
}

/**
  * @brief Get the location of the warehouse.
  */
QString Warehouse::getLocation()
{
    return location;
}

/**
  * @brief Get the list of the products stored in the warehouse.
  */
QList<Product> Warehouse::getProductList()
{
    return productList;
}

/**
  * @brief Get the current capacity of the warehouse.
  */
double Warehouse::getCurrentCapacity()
{
    return warehouseCapacity;
}
