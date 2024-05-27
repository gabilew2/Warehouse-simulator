set(STORAGE_SOURCES
    Storage.h
    Storage.cpp)

add_library(StorageLib ${STORAGE_SOURCES})
target_link_libraries(StorageLib PRIVATE
                      Threads::Threads
                      Qt6::Widgets
                      )

target_include_directories(StorageLib PRIVATE ${INCLUDE_DIR})
