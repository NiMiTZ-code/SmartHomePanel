#include "device.h"

Device::Device(QObject *parent)
    : QObject{parent}
{}

void Device::setDeviceName(QString name)
{
    this->name = name;
}

void Device::setStatus(DeviceStatus st)
{
    status = st;
}

void Device::setCommand(QByteArray comm)
{
    command = comm;
}
