cmake_minimum_required(VERSION 3.14)

project(MedianFilterPlugin LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

set(OpenCV_DIR /usr/local/lib/cmake/opencv4)
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_library(MedianFilterPlugin SHARED
    ../ImageProcessPluginInterface.h
    MedianFilterPlugin_global.h
    MedianFilterPlugin.cpp
    MedianFilterPlugin.h
)

target_link_libraries(MedianFilterPlugin PRIVATE Qt${QT_VERSION_MAJOR}::Core ${OpenCV_LIBRARIES})

target_compile_definitions(MedianFilterPlugin PRIVATE MEDIAN_FILTER_PLUGIN_LIBRARY)
