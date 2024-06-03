#include "Report.h"

/**
 * @brief Construct a new Report object.
 */
Report::Report(double operationalCosts, double netProfit)
{
    this  -> operationalCosts = operationalCosts;
    this -> netProfit = netProfit;
}

/**
 * @brief Generates a summary report as a QString.
 */
QString Report::generateReport()
{
    QString report;
    report += QString("Operational Costs,%1,Net Profit,%2\n")
                  .arg(operationalCosts)
                  .arg(netProfit);

    return report;
}

