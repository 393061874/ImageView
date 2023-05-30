cmake_minimum_required(VERSION 3.14)

project(MMPoseAPI LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Qt
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

# OpenMMLab
set(ENV{TENSORRT_DIR} "/media/tianshu/fastdata/project/mmlab/TensorRT-8.6.0.12")
find_package(MMDeploy
    PATHS /media/tianshu/fastdata/project/mmlab/mmdeploy/build/install/lib/cmake/MMDeploy
    NO_DEFAULT_PATH REQUIRED)

add_library(MMPosePlugin SHARED
  MMPosePlugin_global.h
  MMPosePlugin.cpp
  MMPosePlugin.h
)

target_link_libraries(MMPosePlugin PRIVATE Qt${QT_VERSION_MAJOR}::Core mmdeploy)

target_compile_definitions(MMPosePlugin PRIVATE MMPOSEAPI_LIBRARY)
