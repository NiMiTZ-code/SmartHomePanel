#ifndef THERMOSTAT_H
#define THERMOSTAT_H

#include "actuator.h"
#include "sensor.h"
class Thermostat : public Actuator, Sensor
{
private:
    float temperatureSetting;
    float temperatureReading;
public:
    explicit Thermostat(QObject *parent = nullptr);
    void readValue() override; //to fire network command of temperature retrieval
    void setTemperatureSetting(float temp);
    void setTemperatureReading(); //only if needed, if not, erase
    float getTemperatureReading;
    float getTemperatureSetting(){
        return temperatureSetting;
    }
    void chngTempSetting();
    void toggle() override;

};

#endif // THERMOSTAT_H
