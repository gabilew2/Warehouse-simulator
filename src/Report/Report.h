#ifndef REPORT_H
#define REPORT_H

#include <QString>

/**
 * @brief Forward declaration of the Product class.
 */
class Product;

/**
 * @class Report
 * @brief Represents a report in the store simulation.
 *
 * This class is responsible for generating reports that summarize the operational costs and net profits.
 */
class Report
{
private:
    double operationalCosts; ///<   Operational costs of the store.
    double netProfit;        ///<   Net profit of the store.

public:
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
};

#endif // REPORT_H
