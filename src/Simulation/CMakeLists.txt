set(SIMULATION_SOURCES
    Simulation.h
    Simulation.cpp)

add_library(SimulationLib ${SIMULATION_SOURCES})
target_link_libraries(SimulationLib PRIVATE
                      Threads::Threads
                      Qt6::Widgets
                      )

target_include_directories(SimulationLib PRIVATE ${INCLUDE_DIR})
