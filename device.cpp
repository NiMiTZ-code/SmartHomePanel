#include "device.h"

Device::Device(QObject *parent)
    : QObject{parent}
{}

void Device::setStatus(DeviceStatus st)
{
    status = st;
}

void Device::setCommand(QByteArray command)
{
    //OR/XOR command with new bits of command
    //albo inaczej, po prostu z buta komenda
}
