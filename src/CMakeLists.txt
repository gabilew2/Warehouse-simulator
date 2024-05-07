set(PROJECT_SOURCES
        main.cpp
)

add_subdirectory(gui)

add_executable(${CMAKE_PROJECT_NAME} ${PROJECT_SOURCES})

target_compile_definitions(${CMAKE_PROJECT_NAME}
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE
    Threads::Threads
    GuiLib
    Qt6::Widgets
)

add_custom_target(${CMAKE_PROJECT_NAME}-run
    COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_PROJECT_NAME}
    DEPENDS ${CMAKE_PROJECT_NAME}
    )
