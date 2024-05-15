set(PRODUCT_SOURCES
    Product.h
    Product.cpp)

add_library(ProductLib ${PRODUCT_SOURCES})
target_link_libraries(ProductLib PRIVATE
                      Threads::Threads
                      Qt6::Widgets
                      )

target_include_directories(ProductLib PRIVATE ${INCLUDE_DIR})
