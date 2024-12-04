#ifndef LAMP_H
#define LAMP_H

#include "actuator.h"

class Lamp : public Actuator
{
public:
    explicit Lamp(QObject *parent = nullptr);
    void toggle() override;
private slots:
    //onToggle z UI
signals:
    //statusChange / toggle
};

#endif // LAMP_H
