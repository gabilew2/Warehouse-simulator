#ifndef SALESREPORT_H
#define SALESREPORT_H

#include <Report/Report.h>
#include <QDateTime>
#include <QList>
#include <Warehouse/Warehouse.h>

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
    int SalesId; ///< Unique identifier for the sales report.
    QDateTime time; ///< The time when the report is generated.
    QList<Product> productList; ///< List of products included in the sales report.

public:
    /**
     * @brief Generates a detailed sales report.
     * @return A formatted string representing the sales report.
     */
    QString generateReport();
};

#endif
