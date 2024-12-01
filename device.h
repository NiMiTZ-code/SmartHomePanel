#ifndef DEVICE_H
#define DEVICE_H

#include <QObject>

class Device : public QObject
{
    Q_OBJECT
private:
    QString name;
    QString status;
    quint32 deviceID;
public:
    explicit Device(QObject *parent = nullptr);
    QString getStatus();
    QString getName();
    void sendCommand();
    void setDeviceID();


signals:
};

#endif // DEVICE_H
