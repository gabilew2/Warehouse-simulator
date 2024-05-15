set(WAREHOUSEREPORT_SOURCES
    WarehouseReport.h
    WarehouseReport.cpp)

add_library(WarehouseReportLib ${WAREHOUSEREPORT_SOURCES})
target_link_libraries(WarehouseReportLib PRIVATE
                      Threads::Threads
                      Qt6::Widgets
                      )

target_include_directories(WarehouseReportLib PRIVATE ${INCLUDE_DIR})
