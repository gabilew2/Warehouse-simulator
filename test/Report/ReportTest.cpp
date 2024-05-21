#include <gtest/gtest.h>
#include "Report/Report.h"

/**
 * @brief Test to ensure that the generateReport method does not return an empty string.
 */
TEST(ReportTest, generateReportShouldReturnNonEmptyString)
{
    Report report(1000.0, 500.0);

    QString reportString = report.generateReport();

    EXPECT_FALSE(reportString.isEmpty());
}

/**
 * @brief Test to ensure that the generateReport method returns a string in the expected format.
 */
TEST(ReportTest, GenerateReportShouldReturnExpectedFormat)
{
    Report report(1000.0, 500.0);

    QString reportString = report.generateReport();

    EXPECT_TRUE(reportString.contains("Operational Costs"));
    EXPECT_TRUE(reportString.contains("Net Profit"));
}
