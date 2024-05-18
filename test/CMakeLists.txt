set(TEST_MAIN ${CMAKE_CURRENT_LIST_DIR}/main.cpp)

include(GoogleTest)
include(${CMAKE_BASE_LIST_DIR}/cmake/add_ut.cmake)

set_property(GLOBAL PROPERTY ALL_TESTS_LIST)

find_package(Qt6 REQUIRED COMPONENTS Widgets Test)

add_subdirectory(Event)
add_subdirectory(Product)
add_subdirectory(Report)
add_subdirectory(SalesReport)
add_subdirectory(Simulation)
add_subdirectory(Storage)
add_subdirectory(Warehouse)
add_subdirectory(WarehouseReport)

get_property(ALL_TESTS_LIST GLOBAL PROPERTY ALL_TESTS_LIST)

add_custom_target(all_tests
    DEPENDS
    ${ALL_TESTS_LIST}
    COMMAND ctest)
