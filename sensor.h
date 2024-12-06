#ifndef SENSOR_H
#define SENSOR_H

#include "device.h"

class Sensor : public Device
{
public:
    explicit Sensor(QObject *parent = nullptr);
    virtual void readValue() = 0;
private:
    float readingValue;
};

#endif // SENSOR_H
