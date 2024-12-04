#ifndef DEVICE_H
#define DEVICE_H

#include <QObject>
#include <QHostAddress>

enum class DeviceStatus {
    OFF = 0,
    ON = 1,
    ERROR = 2
};
class Device : public QObject
{
    Q_OBJECT

public:

    explicit Device(QObject *parent = nullptr);
    DeviceStatus getStatus(){
        return status;
    }
    QString getName(){
        return name;
    }
    void setStatus(DeviceStatus st);
    void setCommand(QByteArray comm);
    QByteArray getCurrentCommand() const{
        return command;
    }
    void sendCommand();
private:
    QString name;
    DeviceStatus status;
    QHostAddress deviceIP;
    QByteArray command;

signals:
};

#endif // DEVICE_H
