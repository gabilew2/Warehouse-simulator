#include <gtest/gtest.h>
#include "Product/Product.h"
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
    Product::resetProductId();
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
    Product::resetProductId();
    Warehouse warehouse = Warehouse(QString::fromStdString("Lorem Ipsum"), 1);
    warehouse.addProduct(QString::fromStdString("Lorem Ipsum"), 100, 1);
    EXPECT_EQ(warehouse.checkStatus(), FULLY);

    warehouse.updateStatus(10);
    warehouse.addProduct(QString::fromStdString("Lorem Ipsum"), 100, 9);
    warehouse.changeQuantity(2, 1);
    EXPECT_EQ(warehouse.checkStatus(), FULLY);
}

/**
 * @brief Test to check if the warehouse status is AVAILABLE when capacity is not full.
 */
TEST(WarehouseTest, checkStatusShouldReturnAvailable)
{
    Product::resetProductId();
    Warehouse warehouse = Warehouse(QString::fromStdString("Lorem Ipsum"), 2);
    warehouse.addProduct(QString::fromStdString("Lorem Ipsum"), 99.99, 1);
    EXPECT_EQ(warehouse.checkStatus(), AVAILABLE);

    warehouse.updateStatus(10);
    warehouse.addProduct(QString::fromStdString("Lorem Ipsum"), 99.99, 8);
    warehouse.changeQuantity(2, 1);
    EXPECT_EQ(warehouse.checkStatus(), AVAILABLE);
}

/**
 * @brief Test to verify that updateStatus successfully updates the warehouse's capacity.
 */
TEST(WarehouseTest, updateStatusShouldReturnSuccess)
{
    Product::resetProductId();
    Warehouse warehouse = Warehouse(QString::fromStdString("Lorem Ipsum"), 0);
    EXPECT_EQ(warehouse.updateStatus(10), SUCCESS);
    EXPECT_EQ(warehouse.updateStatus(0), SUCCESS);
    EXPECT_EQ(warehouse.updateStatus(567.97), SUCCESS);

    warehouse.addProduct(QString::fromStdString("Lorem Ipsum"), 99.99, 5);
    EXPECT_EQ(warehouse.updateStatus(1), ERROR);
}

/**
 * @brief Test to verify that updateStatus returns an error when given a negative capacity.
 */
TEST(WarehouseTest, updateStatusShouldReturnError)
{
    Product::resetProductId();
    Warehouse warehouse = Warehouse(QString::fromStdString("Lorem Ipsum"), 567);
    EXPECT_EQ(warehouse.updateStatus(-1), ERROR);

    warehouse.addProduct(QString::fromStdString("Lorem Ipsum"), 100, 5);
    EXPECT_EQ(warehouse.updateStatus(1), ERROR);
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
    Product::resetProductId();
    Warehouse warehouse(testLocation, initialCapacity);
    warehouse.addProduct(productName, productPrice, productQuantity);
    EXPECT_EQ(warehouse.changeQuantity(30, 1), SUCCESS);
    EXPECT_EQ(warehouse.getQuantity(1), 30);
}

/**
 * @brief Test to verify that changeQuantity returns an error when given a negative quantity.
 */
TEST(WarehouseTest, changeQuantityShouldReturnError)
{
    Product::resetProductId();
    Warehouse warehouse(testLocation, initialCapacity);
    warehouse.addProduct(productName, productPrice, productQuantity);
    EXPECT_EQ(warehouse.changeQuantity(-5, 1), ERROR);
}

/**
 * @brief Test to verify that sell successfully sells the product and decreases the quantity.
 */
TEST(WarehouseTest, sellShouldReturnSuccess)
{
    Product::resetProductId();
    Warehouse warehouse(testLocation, initialCapacity);
    warehouse.addProduct(productName, productPrice, productQuantity);
    EXPECT_EQ(warehouse.sell(5, 1), SUCCESS);
    EXPECT_EQ(warehouse.getQuantity(1), productQuantity - 5);
}

/**
 * @brief Test to verify that sell returns an error when trying to sell more than available quantity.
 */
TEST(WarehouseTest, sellShouldReturnError)
{
    Product::resetProductId();
    Warehouse warehouse(testLocation, initialCapacity);
    warehouse.addProduct(productName, productPrice, productQuantity);
    EXPECT_EQ(warehouse.sell(productQuantity + 1, 1), ERROR);
}

/**
 * @brief Test to verify that updatePrice successfully updates the price of a product.
 */
TEST(WarehouseTest, updatePriceShouldReturnSuccess)
{
    Product::resetProductId();
    Warehouse warehouse(testLocation, initialCapacity);
    warehouse.addProduct(productName, productPrice, productQuantity);
    EXPECT_EQ(warehouse.updatePrice(15.0, 1), SUCCESS);
    EXPECT_EQ(warehouse.getPrice(1), 15.0);
}

/**
 * @brief Test to verify that updatePrice returns an error when given a negative price.
 */
TEST(WarehouseTest, updatePriceShouldReturnError)
{
    Product::resetProductId();
    Warehouse warehouse(testLocation, initialCapacity);
    warehouse.addProduct(productName, productPrice, productQuantity);
    EXPECT_EQ(warehouse.updatePrice(-1.0, 1), ERROR);
}

/**
 * @brief Test to verify that addProduct successfully adds a product to the warehouse.
 */
TEST(WarehouseTest, addProductShouldReturnSuccess)
{
    Product::resetProductId();
    Warehouse warehouse(testLocation, initialCapacity);
    EXPECT_EQ(warehouse.addProduct(productName, productPrice, productQuantity), SUCCESS);
    EXPECT_EQ(warehouse.getProductList().size(), 1);
}

/**
 * @brief Test to verify that addProduct returns an error when given a negative price or quantity.
 */
TEST(WarehouseTest, addProductShouldReturnError)
{
    Product::resetProductId();
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
    Product::resetProductId();
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
    Product::resetProductId();
    Warehouse warehouse(testLocation, initialCapacity);
    warehouse.addProduct(productName, productPrice, productQuantity);
    EXPECT_EQ(warehouse.getName(1), productName);
}

/**
 * @brief Test to verify that getPrice returns the correct price of a product by its ID.
 */
TEST(WarehouseTest, getPriceShouldReturnCorrectValue)
{
    Product::resetProductId();
    Warehouse warehouse(testLocation, initialCapacity);
    warehouse.addProduct(productName, productPrice, productQuantity);
    EXPECT_EQ(warehouse.getPrice(1), productPrice);
}

/**
 * @brief Test to verify that getQuantity returns the correct quantity of a product by its ID.
 */
TEST(WarehouseTest, getQuantityShouldReturnCorrectValue)
{
    Product::resetProductId();
    Warehouse warehouse(testLocation, initialCapacity);
    warehouse.addProduct(productName, productPrice, productQuantity);
    EXPECT_EQ(warehouse.getQuantity(1), productQuantity);
}
