cmake_minimum_required(VERSION 3.16)

project(drfc_qt LANGUAGES CXX)

# Enable Qt's automatic processing of UI, MOC, and resources
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find the required Qt packages
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Network Widgets SerialPort)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Network Widgets SerialPort)

# Add the executable target
add_executable(drfc_qt
  main.cpp
  DataTransmissionHandler.cpp
  gui.h gui.cpp
  DataTransmissionWorker.h DataTransmissionWorker.cpp

)

# Ensure the include directories are properly set
target_include_directories(drfc_qt PRIVATE
  ${Qt${QT_VERSION_MAJOR}Core_INCLUDE_DIRS}
  ${Qt${QT_VERSION_MAJOR}Network_INCLUDE_DIRS}
)

# Link the executable with the necessary Qt libraries
target_link_libraries(drfc_qt
  Qt${QT_VERSION_MAJOR}::Core
  Qt${QT_VERSION_MAJOR}::Network
  Qt${QT_VERSION_MAJOR}::Widgets
  Qt${QT_VERSION_MAJOR}::SerialPort
)

# Install rules
include(GNUInstallDirs)
install(TARGETS drfc_qt
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
