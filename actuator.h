#ifndef ACTUATOR_H
#define ACTUATOR_H

#include "device.h"

class Actuator : public Device
{
public:
    explicit Actuator(QObject *parent = nullptr);
    virtual void toggle() = 0;
private:

};

#endif // ACTUATOR_H
