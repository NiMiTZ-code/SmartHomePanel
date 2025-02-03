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
    //TESTY
    NetworkHandler* networkHandler = new NetworkHandler();
    RGBLamp* lampa = new RGBLamp();
    lampa->setDeviceIP(QHostAddress("127.0.0.1"));
    networkHandler->registerDevice(lampa);
    lampa->setBrightness(255);
    lampa->chngBrightness();
    lampa->mixColors(255,128,64);
    lampa->chngColor();
    lampa->toggle();

    lampa->setBrightness(255);
    lampa->chngBrightness();
    lampa->mixColors(255,0,0);
    lampa->chngColor();
    lampa->sendCommand();

    lampa->setBrightness(122);
    lampa->chngBrightness();
    lampa->mixColors(0,128,255);
    lampa->chngColor();
    lampa->sendCommand();

    Thermostat therm;
    therm.setTemperatureSetting(25);
    therm.chngTempSetting();
    therm.toggle();
    therm.toggle();
    return a.exec();

}
