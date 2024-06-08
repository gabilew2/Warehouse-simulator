#include "Report.h"

double Report::operationalCosts = 0;
double Report::netProfit = 0;

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
    report += QString("Operational Costs,Net Profit\n%1,%2\n")
                  .arg(operationalCosts)
                  .arg(netProfit);

    return report;
}

// Setters
void Report::setOperationalCosts(double operationalCost)
{
    operationalCosts = operationalCost;
}

void Report::setNetProfit(double Profit)
{
    netProfit = Profit;
}

// Getters
double Report::getOperationalCosts()
{
    return operationalCosts;
}

double Report::getNetProfit()
{
    return netProfit;
}
