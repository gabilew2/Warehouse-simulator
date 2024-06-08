/**
 * @file Report.cpp
 * @brief Source file for the Report class.
 */

#include "Report.h"

double Report::operationalCosts = 0;
double Report::netProfit = 0;

/**
 * @brief Construct a new Report object.
 *
 * @param operationalCosts Operational costs of the store.
 * @param netProfit Net profit of the store.
 */
Report::Report(double operationalCosts, double netProfit)
{
    setOperationalCosts(operationalCosts);
    setNetProfit(netProfit);
}

/**
 * @brief Generates a summary report as a QString.
 *
 * @return QString A summary report of the store's financial status.
 */
QString Report::generateReport() const
{
    return QString("Operational Costs,Net Profit\n%1,%2\n")
        .arg(getOperationalCosts())
        .arg(getNetProfit());
}

// Setters implementation
void Report::setOperationalCosts(double costs)
{
    operationalCosts = costs;
}

void Report::setNetProfit(double profit)
{
    netProfit = profit;
}

// Getters implementation
double Report::getOperationalCosts()
{
    return operationalCosts;
}

double Report::getNetProfit()
{
    return netProfit;
}
