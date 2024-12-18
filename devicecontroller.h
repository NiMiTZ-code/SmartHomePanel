#ifndef DEVICECONTROLLER_H
#define DEVICECONTROLLER_H

#include <QObject>

#include "device.h"

class DeviceController : public QObject
{
    Q_OBJECT
private:
    QList<Device> m_devices;
    //add devices, ręczne dodawanie po ip w okienku dialogowym?
public:
    explicit DeviceController(QObject *parent = nullptr);

    QList<Device> devices() const{
        return m_devices;
    }

signals:
};

#endif // DEVICECONTROLLER_H
