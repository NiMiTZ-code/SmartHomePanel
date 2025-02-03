#include "mainwindow.h"
#include "rgblamp.h"
#include "thermostat.h"
#include "networkhandler.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    NetworkHandler* networkHandler = new NetworkHandler();
    Device* device = new Device();
    networkHandler->registerDevice(device,QHostAddress("192.168.1.100"));
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
    return a.exec();

}
