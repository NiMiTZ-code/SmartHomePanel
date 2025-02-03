#include "thermostat.h"

Thermostat::Thermostat(QObject *parent)
    : Sensor{parent}
{
    setStatus(DeviceStatus::OFF);
    temperatureSetting = 20.0F;
    temperatureReading = 20.0F;
    setDeviceName("Termostat");
}


void Thermostat::readValue()
{
    //request response on demand
    //TODO read only when device is ON, if off wake up
    QByteArray read_command(3,0);
    read_command[0] = 0xFF;
    read_command[1] = 0x00;
    read_command[2] = 0xFF;
    Sensor::setCommand(read_command);
    sendCommand();
}

void Thermostat::setTemperatureSetting(float temp)
{
    if(-10.0F <= temp && temp <=50.0F){
        temperatureSetting = temp;
    }//else ERROR
}

void Thermostat::setTemperatureReading(float temp)
{
    if(-10.0F <= temp && temp <=50.0F){ //in future change ranges to predefined values
        temperatureReading = temp;
    }//else ERROR
}

void Thermostat::chngTempSetting()
{
    QByteArray temp_command = Sensor::getCurrentCommand();
    temp_command[0] = 0x02; //write
    temp_command[1] = getTemperatureSetting();
    temp_command[2] = 0x01; //ON
    Sensor::setCommand(temp_command);
    sendCommand();

    emit temperatureSettingChanged(getTemperatureSetting());
}

void Thermostat::performAction()
{
    if(getTemperatureReading() > getTemperatureSetting()){
        //turn on AC
    }else if(getTemperatureReading() < getTemperatureSetting()){
        //turn on heater
    }else{
        //turn device off
    }
}


void Thermostat::sendCommand()
{
    emit sendCommandSignal(getCurrentCommand(), getDeviceIP());
}

void Thermostat::handleResponse(const QByteArray &response)
{
    if(response[3] == 0x0F){
        //ERROR handling
    }else if(response[0] == 0x01){
        setTemperatureReading(response[1]);
    }
    //do something
}

