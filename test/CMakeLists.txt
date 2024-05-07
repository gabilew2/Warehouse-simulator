set(TEST_MAIN ${CMAKE_CURRENT_LIST_DIR}/main.cpp)

include(GoogleTest)

set_property(GLOBAL PROPERTY ALL_TESTS_LIST)

get_property(ALL_TESTS_LIST GLOBAL PROPERTY ALL_TESTS_LIST)

add_custom_target(all_tests
    DEPENDS
    ${ALL_TESTS_LIST}
    COMMAND ctest)