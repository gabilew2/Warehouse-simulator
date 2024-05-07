cmake_minimum_required(VERSION 3.5)

project(Warehouse-simulator VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(INCLUDE_DIR ${CMAKE_CURRENT_LIST_DIR}/src)
set(TEST_INCLUDE_DIR ${CMAKE_CURRENT_LIST_DIR}/test)
set(CMAKE_BASE_LIST_DIR ${CMAKE_CURRENT_LIST_DIR})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/release-1.10.0.zip
)
FetchContent_MakeAvailable(googletest)

add_subdirectory(src)
include(CTest)
enable_testing()
add_subdirectory(test)
