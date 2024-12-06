#ifndef THERMOSTAT_H
#define THERMOSTAT_H

#include "actuator.h"

class Thermostat : public Actuator
{
private:
    double temperatueSetting;
    double temperatureReading;
public:
    explicit Thermostat(QObject *parent = nullptr);
    void readTemperature(); //to fire network command of temperature retrieval
    void setTemperatureToAchieve(double temp);
    void setTemperatureReading(); //only if needed, if not, erase
    double getTemperatureReading;
    double getTemperatureSetting();
    void toggle() override;

};

#endif // THERMOSTAT_H
