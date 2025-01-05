#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QDateTime>
#include <QCoreApplication>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QDebug>

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
    ~MainWindow();
public slots:
    void zegar();
    void fetchWeatherData();
    //void handleWeatherData(QNetworkReply *reply);

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    QTimer *weatherTimer;
    QNetworkAccessManager *networkManager;
    void fetchWeatherIcon(const QString &iconCode);
    QString lastIconCode;
    bool isRequestInProgress;
};
#endif // MAINWINDOW_H
