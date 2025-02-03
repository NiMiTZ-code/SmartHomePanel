#include "thermostat.h"

Thermostat::Thermostat(QObject *parent)
    : Actuator{parent}
{
    Actuator::setCommand(QByteArray(3,0));
    Actuator::setStatus(DeviceStatus::OFF);
}

void Thermostat::readValue()
{
    QByteArray read_command(3,0);
    read_command[0] = 0xFF;
    read_command[1] = 0x00;
    read_command[2] = 0xFF;
    Sensor::setCommand(read_command);
    //send command and update reading valu ethorugh slots
}

void Thermostat::setTemperatureSetting(float temp)
{
    if(-10.0F <= temp && temp <=50.0F){
        temperatureSetting = temp;
    }//else ERROR
}

void Thermostat::chngTempSetting()
{
    QByteArray temp_command = Actuator::getCurrentCommand();
    temp_command[0] = 0x01; //ew refactor do funkcji
    temp_command[1] = getTemperatureSetting();
    Actuator::setCommand(temp_command);
}

void Thermostat::toggle()
{
    QByteArray temp_command =  Actuator::getCurrentCommand();
    temp_command[0] = 0x01; //ew refactor do funkcji
    if( Actuator::getStatus()== DeviceStatus::ON){
        temp_command[2] = 0x00;
         Actuator::setCommand(temp_command);
        //signal to send command
         Actuator::setStatus(DeviceStatus::OFF);

    } else{
        temp_command[2] = 0x01;
        Actuator::setCommand(temp_command);
        //signal to send command
        Actuator::setStatus(DeviceStatus::ON);
    }
}

void Thermostat::sendCommand()
{

}

