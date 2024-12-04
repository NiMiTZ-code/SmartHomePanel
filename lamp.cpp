#include "lamp.h"

Lamp::Lamp(QObject *parent)
    : Actuator{parent}
{}

void Lamp::toggle()
{
    QByteArray comm(2,0);
    if(getStatus()== DeviceStatus::ON){
        comm[1] = 0x00;
        setCommand(comm);
        //signal to send command
        setStatus(DeviceStatus::OFF);

    } else{
        comm[1] = 0x01;
        setCommand(comm);
        //signal to send command
        setStatus(DeviceStatus::ON);
    }
}


