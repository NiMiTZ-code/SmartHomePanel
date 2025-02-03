#include "lamp.h"

Lamp::Lamp(QObject *parent)
    : Actuator{parent}
{
    setDeviceName("Lamp");
}

void Lamp::toggle()
{
    QByteArray temp_command(1,0); //1Bajt
    if(getStatus()== DeviceStatus::ON){
        temp_command[0] = 0x00;
        setCommand(temp_command);
        sendCommand();
        setStatus(DeviceStatus::OFF);

    } else{
        temp_command[0] = 0x01;
        setCommand(temp_command);
        sendCommand();
        setStatus(DeviceStatus::ON);
    }
}

void Lamp::sendCommand()
{
    emit sendCommandSignal(getCurrentCommand(), getDeviceIP());
}

void Lamp::onUIToggle()
{
    toggle();
}


