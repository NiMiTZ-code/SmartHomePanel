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
    //OR/XOR command with new bits of command
    //albo inaczej, po prostu z buta komenda
    //this->command = 0x00; //chwilowo zeruje wszystko, więc nie jest idealnie
    command = comm;


}
