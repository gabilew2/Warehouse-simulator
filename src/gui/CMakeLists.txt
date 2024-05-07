set(GUI_SOURCES
    gui.h
    gui.cpp
    gui.ui)

add_library(GuiLib ${GUI_SOURCES})
target_link_libraries(GuiLib PRIVATE
                      Threads::Threads
                      Qt6::Widgets
                      )

target_include_directories(GuiLib PRIVATE ${INCLUDE_DIR})
