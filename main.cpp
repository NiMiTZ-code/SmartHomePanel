#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "rgblamp.h"
#include "thermostat.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("SmartHomePanel", "Main");

    //TESTY
    RGBLamp lampa;
    lampa.getBrightness();
    lampa.setBrightness(255);
    lampa.chngBrightness();
    lampa.mixColors(255,128,64);
    lampa.chngColor();
    lampa.toggle();

    Thermostat therm;
    therm.setTemperatureSetting(25);
    therm.chngTempSetting();
    therm.toggle();
    therm.toggle();

    return app.exec();
}
