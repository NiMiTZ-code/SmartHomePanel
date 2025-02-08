#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "networkhandler.h"
#include "newdevicewindow.h"
#include "qlistwidget.h"
#include "weatherstation.h"
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
    newdevicewindow *addDeviceWindow;
    NetworkHandler *networkHandler;
    WeatherStation *weatherStation;
    QTimer *clockTimer;
    QTimer *weatherTimer;
    void listDevices();
protected:

private slots:
    void on_addDeviceButton_clicked();
    void on_acOnOffButton_clicked();
    void on_devicesListWidget_itemClicked(QListWidgetItem *item);
};
#endif // MAINWINDOW_H
