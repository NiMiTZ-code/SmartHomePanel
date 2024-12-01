#ifndef LAMP_H
#define LAMP_H

#include "actuator.h"

class Lamp : public Actuator
{
public:
    explicit Lamp(QObject *parent = nullptr);
};

#endif // LAMP_H
