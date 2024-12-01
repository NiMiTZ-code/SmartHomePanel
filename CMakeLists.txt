cmake_minimum_required(VERSION 3.16)

project(SmartHomeGUI VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.5 REQUIRED COMPONENTS Quick)

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(appSmartHomeGUI
    main.cpp
)

qt_add_qml_module(appSmartHomeGUI
    URI SmartHomeGUI
    VERSION 1.0
    QML_FILES
        Main.qml
SOURCES actuator.cpp actuator.h device.cpp device.h lamp.cpp lamp.h main.cpp sensor.cpp sensor.h thermostat.cpp thermostat.h weatherstation.cpp weatherstation.h
RESOURCES CMakeLists.txt CMakeLists.txt.user
QML_FILES Main.qml
SOURCES devicecontroller.h devicecontroller.cpp
SOURCES rgblamp.h rgblamp.cpp
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appSmartHomeGUI PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appSmartHomeGUI
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appSmartHomeGUI
    PRIVATE Qt6::Quick
)

include(GNUInstallDirs)
install(TARGETS appSmartHomeGUI
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
