cmake_minimum_required(VERSION 3.14)

project(ImageViewPlugin LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Qt
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

# OpenCV
set(OpenCV_DIR /usr/local/lib/cmake/opencv4)
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_library(ImageViewPlugin SHARED
    ../ImageViewPluginInterface.h
    ImageViewPlugin_global.h
    ImageViewPlugin.h
    ImageViewPlugin.cpp
    ImageView.h
    ImageView.cpp
)

target_link_libraries(ImageViewPlugin PRIVATE Qt${QT_VERSION_MAJOR}::Widgets ${OpenCV_LIBRARIES})

target_compile_definitions(ImageViewPlugin PRIVATE IMAGEVIEWPLUGIN_LIBRARY)
