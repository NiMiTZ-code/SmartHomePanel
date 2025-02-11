#ifndef NEWDEVICEWINDOW_H
#define NEWDEVICEWINDOW_H

#include <QDialog>

namespace Ui {
class newdevicewindow;
}

class newdevicewindow : public QDialog
{
    Q_OBJECT

public:
    explicit newdevicewindow(QWidget *parent = nullptr);
    ~newdevicewindow();
    QString getDeviceName();
    QString getDeviceIP();
    int getDeviceType();
    QString getThermostatName();
    QString getThermostatIP();

private slots:
    void on_deviceTypecBox_activated(int index);

private:
    Ui::newdevicewindow *ui;

};

#endif // NEWDEVICEWINDOW_H
