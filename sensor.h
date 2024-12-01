#ifndef SENSOR_H
#define SENSOR_H

#include "device.h"

class Sensor : public Device
{
public:
    explicit Sensor(QObject *parent = nullptr);
    double readValue();
private:
    double readingValue;
};

#endif // SENSOR_H
