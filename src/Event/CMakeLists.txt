set(EVENT_SOURCES
    Event.h
    Event.cpp)

add_library(EventLib ${EVENT_SOURCES})
target_link_libraries(EventLib PRIVATE
                      Threads::Threads
                      Qt6::Widgets
                      )

target_include_directories(EventLib PRIVATE ${INCLUDE_DIR})
