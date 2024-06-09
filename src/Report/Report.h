/**
 * @file Report.h
 * @brief Header file for the Report class.
 */

#ifndef REPORT_H
#define REPORT_H

#include <QString>

/**
 * @class Report
 * @brief Represents a report in the store simulation.
 *
 * This class is responsible for generating reports that summarize the operational costs and net profits.
 */
class Report
{
private:
    static double operationalCosts; ///< Operational costs of the store.
    static double netProfit;        ///< Net profit of the store.

public:

    /**
     * @struct ProductReport
     * @brief Represents a report for a single product.
     *
     * This structure holds the details of a product for reporting purposes, including its name, price, and quantity.
     */
    struct ProductReport
    {
        QString name;   ///< Name of the product.
        double price;   ///< Price of the product.
        int quantity;   ///< Quantity of the product.
    };

    /**
     * @brief Construct a new Report object.
     *
     * @param operationalCosts Operational costs of the store.
     * @param netProfit Net profit of the store.
     */
    Report(double operationalCosts, double netProfit);

    /**
     * @brief Generates a summary report as a QString.
     *
     * This method compiles the operational costs and net profits into a readable format.
     * @return QString A summary report of the store's financial status.
     */
    QString generateReport() const;

    // Setters
    static void setOperationalCosts(double costs); ///< Set the operational costs.
    static void setNetProfit(double profit);       ///< Set the net profit.

    // Getters
    static double getOperationalCosts(); ///< Get the operational costs.
    static double getNetProfit();        ///< Get the net profit.
};

#endif // REPORT_H
