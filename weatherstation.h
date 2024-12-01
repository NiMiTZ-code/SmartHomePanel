#ifndef WEATHERSTATION_H
#define WEATHERSTATION_H

#include "sensor.h"

class WeatherStation : public Sensor
{
public:
    explicit WeatherStation(QObject *parent = nullptr);
};

#endif // WEATHERSTATION_H
