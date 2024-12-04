#include "lamp.h"

Lamp::Lamp(QObject *parent)
    : Actuator{parent}
{}

void Lamp::toggle()
{
    QByteArray comm(1,0); //1Bajt
    if(getStatus()== DeviceStatus::ON){
        comm[0] = 0x00;
        setCommand(comm);
        //signal to send command
        setStatus(DeviceStatus::OFF);

    } else{
        comm[0] = 0x01;
        setCommand(comm);
        //signal to send command
        setStatus(DeviceStatus::ON);
    }
}


