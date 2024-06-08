/**
 * @file ProductTest.cpp
 * @brief Source file of tests for the Product class.
 */

#include <gtest/gtest.h>
#include "Product/Product.h"

/**
 * @brief Test to ensure that a Product object can be instantiated.
 */
TEST(ProductTest, itLives)
{
    Product(0, QString::fromStdString("Lorem Ipsum"), 1.00, 1);
}

/**
 * @brief Test to verify that getName() returns the correct product name.
 */
TEST(ProductTest, getNameShouldReturnName)
{
    Product product = Product(0, QString::fromStdString("Lorem Ipsum"), 1.00, 1);
    EXPECT_EQ(product.getName(),QString::fromStdString("Lorem Ipsum"));
}

/**
 * @brief Test to verify that getQuantity() returns the correct quantity.
 */
TEST(ProductTest, getQuantityShouldReturnInt)
{
    Product product = Product(0, QString::fromStdString("Lorem Ipsum"), 1.00, 1);
    EXPECT_EQ(product.getQuantity(),1);
}

/**
 * @brief Test to verify that getPrice() returns the correct price.
 */
TEST(ProductTest, getPriceShouldReturnDouble)
{
    Product product = Product(0, QString::fromStdString("Lorem Ipsum"), 1.00, 1);
    EXPECT_EQ(product.getPrice(),1.00);
}

/**
 * @brief Test to verify that sell() returns SUCCESS when selling a valid quantity.
 */
TEST(ProductTest, sellShouldReturnSuccess)
{
    Product product = Product(0, QString::fromStdString("Lorem Ipsum"), 1.00, 1);
    Product product2 = Product(1, QString::fromStdString("Ipsum Lorem"), 23.99, 56);
    EXPECT_EQ(product.sell(1),SUCCESS);
    EXPECT_EQ(product2.sell(1),SUCCESS);
    EXPECT_EQ(product2.sell(53),SUCCESS);
    EXPECT_EQ(product2.sell(2),SUCCESS);
}

/**
 * @brief Test to verify that sell() returns ERROR when selling an invalid quantity.
 */
TEST(ProductTest, sellShouldReturnError)
{
    Product product = Product(0, QString::fromStdString("Lorem Ipsum"), 1.00, 0);
    Product product2 = Product(1, QString::fromStdString("Ipsum Lorem"), 23.99, 1);
    EXPECT_EQ(product.sell(1),ERROR);
    EXPECT_EQ(product.sell(-1),ERROR);
    EXPECT_EQ(product2.sell(2),ERROR);
    EXPECT_EQ(product2.sell(-1),ERROR);
}

/**
 * @brief Test to verify that updatePrice() returns SUCCESS when given a valid price.
 */
TEST(ProductTest, updatePriceShouldReturnSuccess)
{
    Product product = Product(0, QString::fromStdString("Lorem Ipsum"), 1.00, 0);
    EXPECT_EQ(product.updatePrice(1.00),SUCCESS);
    EXPECT_EQ(product.updatePrice(59.99),SUCCESS);
    EXPECT_EQ(product.updatePrice(545454),SUCCESS);
    EXPECT_EQ(product.updatePrice(1),SUCCESS);
    EXPECT_EQ(product.updatePrice(0.01),SUCCESS);
}

/**
 * @brief Test to verify that updatePrice() returns ERROR when given an invalid price.
 */
TEST(ProductTest, updatePriceShouldReturnError)
{
    Product product = Product(0, QString::fromStdString("Lorem Ipsum"), 1.00, 0);
    EXPECT_EQ(product.updatePrice(-1.00),ERROR);
    EXPECT_EQ(product.updatePrice(-59.99),ERROR);
    EXPECT_EQ(product.updatePrice(-545454),ERROR);
    EXPECT_EQ(product.updatePrice(-1),ERROR);
    EXPECT_EQ(product.updatePrice(-0.01),ERROR);
}

/**
 * @brief Test to verify that changeQuantity() returns SUCCESS when given a valid quantity.
 */
TEST(ProductTest, changeQuantityShouldReturnSuccess)
{
    Product product = Product(0, QString::fromStdString("Lorem Ipsum"), 1.00, 3);
    EXPECT_EQ(product.changeQuantity(1),SUCCESS);
    EXPECT_EQ(product.changeQuantity(59),SUCCESS);
    EXPECT_EQ(product.changeQuantity(545454),SUCCESS);
}

/**
 * @brief Test to verify that changeQuantity() returns ERROR when given an invalid quantity.
 */
TEST(ProductTest, changeQuantityShouldReturnError)
{
    Product product = Product(0, QString::fromStdString("Lorem Ipsum"), 1.00, 3);
    EXPECT_EQ(product.changeQuantity(-1),ERROR);
    EXPECT_EQ(product.changeQuantity(-59),ERROR);
    EXPECT_EQ(product.changeQuantity(-545454),ERROR);
}
