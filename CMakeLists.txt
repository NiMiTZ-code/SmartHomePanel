cmake_minimum_required(VERSION 3.16)

project(SmartHomePanel VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.5 REQUIRED COMPONENTS Quick)

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(appSmartHomePanel
    main.cpp
)

qt_add_qml_module(appSmartHomePanel
    URI SmartHomePanel
    VERSION 1.0
    QML_FILES
        Main.qml
        SOURCES device.h device.cpp
        SOURCES sensor.h sensor.cpp
        SOURCES actuator.h actuator.cpp
        SOURCES lamp.h lamp.cpp
        SOURCES thermostat.h thermostat.cpp
        SOURCES weatherstation.h weatherstation.cpp
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appSmartHomePanel PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appSmartHomePanel
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appSmartHomePanel
    PRIVATE Qt6::Quick
)

include(GNUInstallDirs)
install(TARGETS appSmartHomePanel
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
