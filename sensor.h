#ifndef SENSOR_H
#define SENSOR_H

#include "device.h"

class Sensor : public Device
{
    Q_OBJECT
public:
    explicit Sensor(QObject *parent = nullptr);
    virtual void readValue() = 0;
    void sendCommand() override;
private:
    float readingValue;
};

#endif // SENSOR_H
