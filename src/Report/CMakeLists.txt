set(REPORT_SOURCES
    Report.h
    Report.cpp)

add_library(ReportLib ${REPORT_SOURCES})
target_link_libraries(ReportLib PRIVATE
                      Threads::Threads
                      Qt6::Widgets
                      )

target_include_directories(ReportLib PRIVATE ${INCLUDE_DIR})
