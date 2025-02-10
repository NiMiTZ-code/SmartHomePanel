#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "networkhandler.h"
#include "newdevicewindow.h"
#include "qframe.h"
#include "weatherstation.h"
#include "device.h"
#include <QMap>
//#include <QTimer>
//#include <QDateTime>
//#include <QCoreApplication>
//#include <QNetworkAccessManager>
//#include <QNetworkRequest>
//#include <QNetworkReply>
//#include <QJsonDocument>
//#include <QJsonObject>
//#include <QJsonArray>
//#include <QJsonValue>
//#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    MainWindow(NetworkHandler *networkHandler = nullptr, QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void setTime();
    void setWeatherData();
    void updateWeatherData();
private:
    Ui::MainWindow *ui;
    QMap<Device*, QFrame*> deviceCards;

    newdevicewindow *addDeviceWindow;
    NetworkHandler *networkHandler;
    WeatherStation *weatherStation;
    QTimer *clockTimer;
    QTimer *weatherTimer;
    Device *currentDevice;

    Device* searchForDevice(QString deviceName);
    void removeDeviceCard(Device* device);
protected:

private slots:
    void on_addDeviceButton_clicked();
    void addDeviceCard(Device* device);
};
#endif // MAINWINDOW_H
