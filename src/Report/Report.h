#ifndef REPORT_H
#define REPORT_H

#include <QString>

class Report
{
private:
    double operationalCosts;
    double netProfit;
public:
    QString generateReport();
};

#endif
