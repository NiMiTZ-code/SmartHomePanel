#include "mainwindow.h"
#include "ui_mainwindow.h"

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
