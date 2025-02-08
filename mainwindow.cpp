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
    , ui(new Ui::MainWindow), weatherStation(new WeatherStation(this))
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
    Device newDevice;
    AC newAC;
    if(result){
        switch(addDeviceWindow->getDeviceType()){
        case 0:
            //ac
            //newAC.setDeviceName(addDeviceWindow->getDeviceName());
            //adres.setAddress(addDeviceWindow->getDeviceIP());
            //newAC.setDeviceIP(adres);
            networkHandler->registerDevice(new AC);

            qDebug() << addDeviceWindow->getDeviceName();
            qDebug() << addDeviceWindow->getDeviceIP();
            break;
        case 1:
            //heater
            networkHandler->registerDevice(new Heater);

            qDebug() << addDeviceWindow->getDeviceName();
            qDebug() << addDeviceWindow->getDeviceIP();
            break;
        case 2:
            //RGBLamp
            networkHandler->registerDevice(new RGBLamp);

            qDebug() << addDeviceWindow->getDeviceName();
            qDebug() << addDeviceWindow->getDeviceIP();
            break;
        case 3:
            //Thermostat
            networkHandler->registerDevice(new Thermostat);

            qDebug() << addDeviceWindow->getDeviceName();
            qDebug() << addDeviceWindow->getDeviceIP();
            break;
        }
        listDevices();

    }

    //newitem->setText(networkHandler->m_devices[1]->getName());
    //ui->devicesListWidget->addItem(newitem);
    //ui->devicesListWidget->update();
    delete addDeviceWindow;
}

void MainWindow::listDevices(){
    QListWidgetItem *item = new QListWidgetItem;
    QList<Device*> devices = networkHandler->getDevices(); //wskazniki
    for(Device* device: devices){
        item->setText(device->getName());
        ui->devicesListWidget->addItem(item);
    }
    ui->devicesListWidget->update();
}
