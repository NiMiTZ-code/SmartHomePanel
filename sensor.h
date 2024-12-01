#ifndef SENSOR_H
#define SENSOR_H

#include "device.h"

class Sensor : public Device
{
public:
    explicit Sensor(QObject *parent = nullptr);
};

#endif // SENSOR_H
