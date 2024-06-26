/**
 * @file SalesReport.h
 * @brief Header file for the SalesReport class.
 */

#ifndef SALESREPORT_H
#define SALESREPORT_H

#include "Report/Report.h"
#include <QDateTime>
#include <QList>

/**
 * @class SalesReport
 * @brief The SalesReport class extends the Report class to provide a report specifically for sales.
 *
 * This class inherits from Report and is responsible for generating a sales report,
 * which includes details such as sales ID, time, and a list of products sold.
 */
class SalesReport : Report
{
private:
    int salesId; ///< Unique identifier for the sales report.
    QDateTime time; ///< The time when the report is generated.
    QList<ProductReport> productList; ///< List of products included in the sales report.

public:
    /**
     * @brief Construct a new SalesReport object.
     *
     * @param salesId Unique identifier for the sales report.
     * @param time The time when the report is generated.
     * @param productList List of products included in the sales report.
     * @param operationalCosts Operational costs of the store.
     * @param netProfit Net profit of the store.
     */
    SalesReport(int salesId, QDateTime time, QList<ProductReport> productList, double operationalCosts, double netProfit);

    /**
     * @brief Generates a detailed sales report.
     * @return QString A formatted string representing the sales report.
     */
    QString generateReport() const;
};

#endif // SALESREPORT_H
