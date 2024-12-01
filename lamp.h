#ifndef LAMP_H
#define LAMP_H

#include "actuator.h"

class Lamp : public Actuator
{
public:
    explicit Lamp(QObject *parent = nullptr);
    void toggle() override;
};

#endif // LAMP_H
