cmake_minimum_required(VERSION 3.0.0)

project("GT RoboJackets RoboCup")


# include cmake files in the 'cmake folder'
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

# put executables in the 'run' folder
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/run)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/run)

# Qt5
find_package(Qt5Widgets)

# Google Protobuf
find_package(Protobuf REQUIRED)
include_directories(${PROTOBUF_INCLUDE_DIR})

# Python
find_package(PythonInterp 3.2 REQUIRED)
find_package(PythonLibs 3.2 REQUIRED)

# Eigen - used for linear algebra
find_package(Eigen3 REQUIRED)
include_directories(${EIGEN_INCLUDE_DIR})

# libusb
find_package(libusb-1.0 REQUIRED)

# Several things depend on the headers in the 'common' directory
include_directories("${PROJECT_SOURCE_DIR}/common") # for headers in common/
include_directories("${PROJECT_BINARY_DIR}/common") # for generated protobuf headers

# run all the other CMakeLists files
add_subdirectory(test)
add_subdirectory(common)
add_subdirectory(soccer)
add_subdirectory(simulator)
add_subdirectory(logging)
add_subdirectory(firmware)
