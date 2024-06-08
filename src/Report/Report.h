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
    static double operationalCosts; ///<   Operational costs of the store.
    static double netProfit;        ///<   Net profit of the store.

public:

    /**
     * @struct ProductReport
     * @brief Represents a report for a single product.
     *
     * This structure holds the details of a product for reporting purposes, including its name, price, and quantity.
     */
    struct ProductReport
    {
        QString name;
        double price;
        int quantity;
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
    QString generateReport();

    // Setters
    static void setOperationalCosts(double operationalCost); ///< Set value of operationalCosts.
    static void setNetProfit(double Profit);                 ///< Set value of netProfit.

    //Getters
    static double getOperationalCosts();          ///< Get value of operationalCosts.
    static double getNetProfit();                 ///< Get value of netProfit.
};

#endif // REPORT_H
