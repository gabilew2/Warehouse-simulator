set(SALESREPORT_SOURCES
    SalesReport.h
    SalesReport.cpp)

add_library(SalesReportLib ${SALESREPORT_SOURCES})
target_link_libraries(SalesReportLib PRIVATE
                      Threads::Threads
                      Qt6::Widgets
                      )

target_include_directories(SalesReportLib PRIVATE ${INCLUDE_DIR})
