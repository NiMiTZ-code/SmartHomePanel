#include "lamp.h"

Lamp::Lamp(QObject *parent)
    : Actuator{parent}
{}

void Lamp::toggle()
{
    QByteArray temp_command(1,0); //1Bajt
    if(getStatus()== DeviceStatus::ON){
        temp_command[0] = 0x00;
        setCommand(temp_command);
        //signal to send command
        setStatus(DeviceStatus::OFF);

    } else{
        temp_command[0] = 0x01;
        setCommand(temp_command);
        //signal to send command
        setStatus(DeviceStatus::ON);
    }
}


