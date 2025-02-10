#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "networkhandler.h"
#include "ac.h"
#include "heater.h"
#include "rgblamp.h"
#include "thermostat.h"
//#include "device.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), weatherStation(new WeatherStation(this)), currentDevice(nullptr)
{
    ui->setupUi(this);
    // Timer to update the time every second
    clockTimer = new QTimer(this);
    connect(clockTimer, &QTimer::timeout, this, &MainWindow::setTime);
    clockTimer->start(1000);

    // Timer to update the weather every 60 seconds (1 minute)
    weatherTimer = new QTimer(this);
    connect(weatherTimer, &QTimer::timeout, this, &MainWindow::updateWeatherData);
    weatherTimer->start(300000);  // Refresh weather every 5 minutes 300000

    connect(weatherStation, &WeatherStation::weatherUpdated, this, &MainWindow::setWeatherData);

}

MainWindow::MainWindow(NetworkHandler *networkhandler, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), networkHandler(networkhandler), weatherStation(new WeatherStation(this))
{
    ui->setupUi(this);
    // Timer to update the time every second
    clockTimer = new QTimer(this);
    connect(clockTimer, &QTimer::timeout, this, &MainWindow::setTime);
    clockTimer->start(1000);

    // Timer to update the weather every 60 seconds (1 minute)
    weatherTimer = new QTimer(this);
    connect(weatherTimer, &QTimer::timeout, this, &MainWindow::updateWeatherData);
    weatherTimer->start(300000);  // Refresh weather every 5 minutes 300000

    connect(weatherStation, &WeatherStation::weatherUpdated, this, &MainWindow::setWeatherData);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setTime(){
    ui->timeLabel->setText(weatherStation->acquireTime());
}

void MainWindow::setWeatherData(){
    //qDebug() << "Seting weather data.";
    ui->temperatureLabel->setText(weatherStation->getTemperature());
    ui->humidityLabel->setText(weatherStation->getHumidity());
    ui->pressureLabel->setText(weatherStation->getPressure());
    ui->weatherIconLabel->setPixmap(QPixmap::fromImage(weatherStation->getIconImage()));
}

void MainWindow::updateWeatherData(){
    weatherStation->readValue();
}

void MainWindow::on_addDeviceButton_clicked()
{
    addDeviceWindow = new newdevicewindow(this);
    int result = addDeviceWindow->exec();
    QHostAddress adres;
    AC *newAC;
    Heater *newHeater;
    RGBLamp *newRGBLamp;
    Thermostat *newThermostat;
    if(result){
        switch(addDeviceWindow->getDeviceType()){
        case 0:
            //ac
            newAC = new AC;
            newAC->setDeviceName(addDeviceWindow->getDeviceName());
            adres.setAddress(addDeviceWindow->getDeviceIP());
            newAC->setDeviceIP(adres);
            networkHandler->registerDevice(newAC);

            qDebug() << addDeviceWindow->getDeviceName();
            qDebug() << addDeviceWindow->getDeviceIP();
            break;
        case 1:
            //heater
            newHeater = new Heater;
            newHeater->setDeviceName(addDeviceWindow->getDeviceName());
            adres.setAddress(addDeviceWindow->getDeviceIP());
            newHeater->setDeviceIP(adres);
            networkHandler->registerDevice(newHeater);

            qDebug() << addDeviceWindow->getDeviceName();
            qDebug() << addDeviceWindow->getDeviceIP();
            break;
        case 2:
            //RGBLamp
            newRGBLamp = new RGBLamp;
            newRGBLamp->setDeviceName(addDeviceWindow->getDeviceName());
            adres.setAddress(addDeviceWindow->getDeviceIP());
            newRGBLamp->setDeviceIP(adres);
            networkHandler->registerDevice(newRGBLamp);

            qDebug() << addDeviceWindow->getDeviceName();
            qDebug() << addDeviceWindow->getDeviceIP();
            break;
        case 3:
            //Thermostat
            newThermostat = new Thermostat;
            newThermostat->setDeviceName(addDeviceWindow->getDeviceName());
            adres.setAddress(addDeviceWindow->getDeviceIP());
            newThermostat->setDeviceIP(adres);
            networkHandler->registerDevice(newThermostat);

            qDebug() << addDeviceWindow->getDeviceName();
            qDebug() << addDeviceWindow->getDeviceIP();
            break;
        }
        listDevices();
    }
    delete addDeviceWindow;
}

void MainWindow::listDevices(){
    QListWidgetItem *item = new QListWidgetItem;
    QList<Device*> devices = networkHandler->getDevices(); //wskazniki
    for(Device* device: devices){
        item->setText(device->getName());
        //problem ze wszystkie się nazywają tak samo więc musiało by być jakieś oznaczenie typu?
        //if(device->getName()=="A/C"){
        //    QString status;
        //    switch(device->getStatus()){
        //    case DeviceStatus::ON:
        //        ui->acStatusLabel->setText("ON");
        //        break;
        //    case DeviceStatus::OFF:
        //        ui->acStatusLabel->setText("OFF");
        //        break;
        //    case DeviceStatus::ERROR:
        //        ui->acStatusLabel->setText("ERROR");
        //        break;
        //    }
        //}
        ui->devicesListWidget->addItem(item);
    }
    ui->devicesListWidget->update();
}

Device* MainWindow::searchForDevice(QString deviceName)
{
    Device *selectedDevice = nullptr;
    // Znalezienie urządzenia na podstawie nazwy
    for (Device* device : networkHandler->getDevices()) {
        if (device->getName() == deviceName) {
            selectedDevice = device;
            break;
        }
    }
    return selectedDevice;
}

void MainWindow::on_acOnOffButton_clicked() {

}

void MainWindow::on_devicesListWidget_itemDoubleClicked(QListWidgetItem *item)
{
    QString deviceName = item->text();
    Device *selectedDevice = searchForDevice(deviceName);

    if (selectedDevice != nullptr) {
        currentDevice = selectedDevice;
        //connect(currentDevice, &Device::statusChanged, this, &MainWindow::updateDeviceInfo);
        //connect(currentDevice, &Device::deviceNameChanged, this, &MainWindow::updateDeviceInfo);
        updateDeviceInfo(selectedDevice);
    }
}

void MainWindow::on_deviceOnOffButton_clicked() //toggle
{
    if(RGBLamp* rgbLamp = qobject_cast<RGBLamp*>(currentDevice)){
        rgbLamp->toggle();
    }
    else if(AC* ac = qobject_cast<AC*>(currentDevice)){
        ac->toggle();
    }
    else if(Heater* heater = qobject_cast<Heater*>(currentDevice)){
        heater->toggle();
    }
    else {
        qDebug() << "Device type invalid.";
    }

}

void MainWindow::updateDeviceInfo(Device* currDev)
{
    if (currDev) {
        QString statusText;
        switch (currDev->getStatus()) {
        case DeviceStatus::ON:
            statusText = "ON";
            break;
        case DeviceStatus::OFF:
            statusText = "OFF";
            break;
        case DeviceStatus::ERROR:
            statusText = "ERROR";
            break;
        }

        QString deviceInfo = QString("Name: %1\nType: %2\nStatus: %3\nIP: %4")
                                 .arg(currDev->getName())
                                 .arg(QString(typeid(*currDev).name()).remove("class ").remove("struct "))
                                 .arg(statusText)
                                 .arg(currDev->getDeviceIP().toString());

        ui->deviceInfoLabel->setText(deviceInfo);
        ui->deviceStatusLabel->setText(statusText);
        ui->deviceNameLabel->setText(currDev->getName());
    }
}
