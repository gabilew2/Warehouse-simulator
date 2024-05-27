set(WAREHOUSE_SOURCES
    Warehouse.h
    Warehouse.cpp)

add_library(WarehouseLib ${WAREHOUSE_SOURCES})
target_link_libraries(WarehouseLib PRIVATE
                      Threads::Threads
                      Qt6::Widgets
                      )

target_include_directories(WarehouseLib PRIVATE ${INCLUDE_DIR})
