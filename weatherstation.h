#ifndef WEATHERSTATION_H
#define WEATHERSTATION_H

#include "sensor.h"

class WeatherStation : public Sensor
{
    Q_OBJECT
public:
    explicit WeatherStation(QObject *parent = nullptr);
};

#endif // WEATHERSTATION_H
