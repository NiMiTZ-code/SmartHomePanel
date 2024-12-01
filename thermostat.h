#ifndef THERMOSTAT_H
#define THERMOSTAT_H

#include "actuator.h"

class Thermostat : public Actuator
{
public:
    explicit Thermostat(QObject *parent = nullptr);
};

#endif // THERMOSTAT_H
