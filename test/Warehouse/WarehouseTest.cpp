#include <gtest/gtest.h>
#include "Warehouse/Warehouse.h"

/**
 * @brief Test to ensure that a Warehouse object can be instantiated.
 */
TEST(WarehouseTest, itLives)
{
    Warehouse warehouse = Warehouse(QString::fromStdString("Lorem Ipsum"), 532);
}

/**
 * @brief Test to check if the warehouse status is EMPTY when capacity is zero or after products are removed.
 */
TEST(WarehouseTest, checkStatusShouldReturnEmpty)
{
    Warehouse warehouse = Warehouse(QString::fromStdString("Lorem Ipsum"), 0);
    EXPECT_EQ(warehouse.checkStatus(), EMPTY);

    warehouse.updateStatus(10);
    warehouse.addProduct(QString::fromStdString("Lorem Ipsum"), 99.99, 10);
    warehouse.changeQuantity(0, 1);
    EXPECT_EQ(warehouse.checkStatus(), EMPTY);
}

/**
 * @brief Test to check if the warehouse status is FULLY when capacity is full or exceeded.
 */
TEST(WarehouseTest, checkStatusShouldReturnFully)
{
    Warehouse warehouse = Warehouse(QString::fromStdString("Lorem Ipsum"), 1);
    warehouse.addProduct(QString::fromStdString("Lorem Ipsum"), 99.99, 1);
    EXPECT_EQ(warehouse.checkStatus(), FULLY);

    warehouse.updateStatus(10);
    warehouse.addProduct(QString::fromStdString("Lorem Ipsum"), 99.99, 8);
    warehouse.changeQuantity(1, 3);
    EXPECT_EQ(warehouse.checkStatus(), FULLY);
}

/**
 * @brief Test to check if the warehouse status is AVAILABLE when capacity is not full.
 */
TEST(WarehouseTest, checkStatusShouldReturnAvailable)
{
    Warehouse warehouse = Warehouse(QString::fromStdString("Lorem Ipsum"), 2);
    warehouse.addProduct(QString::fromStdString("Lorem Ipsum"), 99.99, 1);
    EXPECT_EQ(warehouse.checkStatus(), AVAILABLE);

    warehouse.updateStatus(10);
    warehouse.addProduct(QString::fromStdString("Lorem Ipsum"), 99.99, 8);
    warehouse.changeQuantity(0, 5);
    EXPECT_EQ(warehouse.checkStatus(), AVAILABLE);
}

/**
 * @brief Test to verify that updateStatus successfully updates the warehouse's capacity.
 */
TEST(WarehouseTest, updateStatusShouldReturnSuccess)
{
    Warehouse warehouse = Warehouse(QString::fromStdString("Lorem Ipsum"), 0);
    EXPECT_EQ(warehouse.updateStatus(10), SUCCESS);
    EXPECT_EQ(warehouse.updateStatus(0), SUCCESS);
    EXPECT_EQ(warehouse.updateStatus(567.97), SUCCESS);

    warehouse.addProduct(QString::fromStdString("Lorem Ipsum"), 99.99, 5);
    EXPECT_EQ(warehouse.updateStatus(6), SUCCESS);
}

/**
 * @brief Test to verify that updateStatus returns an error when given a negative capacity.
 */
TEST(WarehouseTest, updateStatusShouldReturnError)
{
    Warehouse warehouse = Warehouse(QString::fromStdString("Lorem Ipsum"), 567);
    EXPECT_EQ(warehouse.updateStatus(-1), ERROR);
    EXPECT_EQ(warehouse.updateStatus(-0.3), ERROR);

    warehouse.addProduct(QString::fromStdString("Lorem Ipsum"), 99.99, 5);
    EXPECT_EQ(warehouse.updateStatus(4), ERROR);
}

const QString testLocation = "Test Location";
const double initialCapacity = 100.0;
const QString productName = "Test Product";
const double productPrice = 10.0;
const int productQuantity = 20;

/**
 * @brief Test to verify that changeQuantity successfully changes the quantity of a product.
 */
TEST(WarehouseTest, changeQuantityShouldReturnSuccess)
{
    Warehouse warehouse(testLocation, initialCapacity);
    warehouse.addProduct(productName, productPrice, productQuantity);
    EXPECT_EQ(warehouse.changeQuantity(30, 8), SUCCESS);
    EXPECT_EQ(warehouse.getQuantity(7), 30);
}

/**
 * @brief Test to verify that changeQuantity returns an error when given a negative quantity.
 */
TEST(WarehouseTest, changeQuantityShouldReturnError)
{
    Warehouse warehouse(testLocation, initialCapacity);
    warehouse.addProduct(productName, productPrice, productQuantity);
    EXPECT_EQ(warehouse.changeQuantity(-5, 8), ERROR);
}

/**
 * @brief Test to verify that sell successfully sells the product and decreases the quantity.
 */
TEST(WarehouseTest, sellShouldReturnSuccess)
{
    Warehouse warehouse(testLocation, initialCapacity);
    warehouse.addProduct(productName, productPrice, productQuantity);
    EXPECT_EQ(warehouse.sell(5, 9), SUCCESS);
    EXPECT_EQ(warehouse.getQuantity(9), productQuantity - 5);
}

/**
 * @brief Test to verify that sell returns an error when trying to sell more than available quantity.
 */
TEST(WarehouseTest, sellShouldReturnError)
{
    Warehouse warehouse(testLocation, initialCapacity);
    warehouse.addProduct(productName, productPrice, productQuantity);
    EXPECT_EQ(warehouse.sell(productQuantity + 1, 10), ERROR);
}

/**
 * @brief Test to verify that updatePrice successfully updates the price of a product.
 */
TEST(WarehouseTest, updatePriceShouldReturnSuccess)
{
    Warehouse warehouse(testLocation, initialCapacity);
    warehouse.addProduct(productName, productPrice, productQuantity);
    EXPECT_EQ(warehouse.updatePrice(15.0, 11), SUCCESS);
    EXPECT_EQ(warehouse.getPrice(11), 15.0);
}

/**
 * @brief Test to verify that updatePrice returns an error when given a negative price.
 */
TEST(WarehouseTest, updatePriceShouldReturnError)
{
    Warehouse warehouse(testLocation, initialCapacity);
    warehouse.addProduct(productName, productPrice, productQuantity);
    EXPECT_EQ(warehouse.updatePrice(-1.0, 12), ERROR);
}

/**
 * @brief Test to verify that addProduct successfully adds a product to the warehouse.
 */
TEST(WarehouseTest, addProductShouldReturnSuccess)
{
    Warehouse warehouse(testLocation, initialCapacity);
    EXPECT_EQ(warehouse.addProduct(productName, productPrice, productQuantity), SUCCESS);
    EXPECT_EQ(warehouse.getProductList().size(), 1);
}

/**
 * @brief Test to verify that addProduct returns an error when given a negative price or quantity.
 */
TEST(WarehouseTest, addProductShouldReturnError)
{
    Warehouse warehouse(testLocation, initialCapacity);
    EXPECT_EQ(warehouse.addProduct(productName, -productPrice, productQuantity), ERROR);
}

/**
 * @brief Test to verify that getLocation returns the correct location of the warehouse.
 */
TEST(WarehouseTest, getLocationShouldReturnCorrectValue)
{
    Warehouse warehouse(testLocation, initialCapacity);
    EXPECT_EQ(warehouse.getLocation(), testLocation);
}

/**
 * @brief Test to verify that getProductList returns the correct list of products.
 */
TEST(WarehouseTest, getProductListShouldReturnCorrectValue)
{
    Warehouse warehouse(testLocation, initialCapacity);
    warehouse.addProduct(productName, productPrice, productQuantity);

    QList<Product> productList = warehouse.getProductList();

    ASSERT_EQ(productList.size(), 1);
    EXPECT_EQ(productList[0].getName(), productName);
    EXPECT_EQ(productList[0].getPrice(), productPrice);
    EXPECT_EQ(productList[0].getQuantity(), productQuantity);
}

/**
 * @brief Test to verify that getCurrentCapacity returns the correct current capacity of the warehouse.
 */
TEST(WarehouseTest, getCurrentCapacityShouldReturnCorrectValue)
{
    Warehouse warehouse(testLocation, initialCapacity);
    EXPECT_EQ(warehouse.getCurrentCapacity(), initialCapacity);
}

/**
 * @brief Test to verify that getName returns the correct name of a product by its ID.
 */
TEST(WarehouseTest, getNameShouldReturnCorrectValue)
{
    Warehouse warehouse(testLocation, initialCapacity);
    warehouse.addProduct(productName, productPrice, productQuantity);
    EXPECT_EQ(warehouse.getName(15), productName);
}

/**
 * @brief Test to verify that getPrice returns the correct price of a product by its ID.
 */
TEST(WarehouseTest, getPriceShouldReturnCorrectValue)
{
    Warehouse warehouse(testLocation, initialCapacity);
    warehouse.addProduct(productName, productPrice, productQuantity);
    EXPECT_EQ(warehouse.getPrice(16), productPrice);
}

/**
 * @brief Test to verify that getQuantity returns the correct quantity of a product by its ID.
 */
TEST(WarehouseTest, getQuantityShouldReturnCorrectValue)
{
    Warehouse warehouse(testLocation, initialCapacity);
    warehouse.addProduct(productName, productPrice, productQuantity);
    EXPECT_EQ(warehouse.getQuantity(17), productQuantity);
}
