set(PROJECT_SOURCES
        main.cpp
)

add_subdirectory(gui)
add_subdirectory(Event)
add_subdirectory(Product)
add_subdirectory(Report)
add_subdirectory(SalesReport)
add_subdirectory(Simulation)
add_subdirectory(Storage)
add_subdirectory(Warehouse)
add_subdirectory(WarehouseReport)


add_executable(${CMAKE_PROJECT_NAME} ${PROJECT_SOURCES})

target_compile_definitions(${CMAKE_PROJECT_NAME}
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE
    Threads::Threads
    GuiLib
    EventLib
    ProductLib
    ReportLib
    SalesReportLib
    SimulationLib
    StorageLib
    WarehouseLib
    WarehouseReportLib
    Qt6::Widgets
)

add_custom_target(${CMAKE_PROJECT_NAME}-run
    COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_PROJECT_NAME}
    DEPENDS ${CMAKE_PROJECT_NAME}
    )
