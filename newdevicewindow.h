#ifndef NEWDEVICEWINDOW_H
#define NEWDEVICEWINDOW_H

#include <QDialog>
#include <QHostAddress>

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

    void on_deviceNameLnEdit_textEdited(const QString &arg1);

    void on_deviceIPLnEdit_textEdited(const QString &arg1);

    void on_thermostatNameliEd_textEdited(const QString &arg1);

    void on_thermostatIpLiEd_textEdited(const QString &arg1);

private:
    Ui::newdevicewindow *ui;
    void newDeviceNameAndIpOK();
    void newThermostatNameAndIpOK();
    bool checkIfIpNotInUse(QHostAddress address);


signals:
    QString newDeviceNameCheck(QString name);
    QHostAddress newDeviceIpcheck(QHostAddress *ip);

};

#endif // NEWDEVICEWINDOW_H
