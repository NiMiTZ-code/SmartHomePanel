#ifndef DEVICEWIDGET_H
#define DEVICEWIDGET_H

#include <QWidget>
#include "device.h"

class DeviceWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DeviceWidget(Device* device, QWidget *parent = nullptr)
        : QWidget(parent), m_device(device) {}
    virtual void updateUI() = 0;
protected:
    Device* m_device;

signals:
};

#endif // DEVICEWIDGET_H
