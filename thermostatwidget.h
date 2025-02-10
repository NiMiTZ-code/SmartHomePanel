#ifndef THERMOSTATWIDGET_H
#define THERMOSTATWIDGET_H

#include <QWidget>
#include "devicewidget.h"
#include "thermostat.h"

namespace Ui {
class ThermostatWidget;
}

class ThermostatWidget : public DeviceWidget
{
    Q_OBJECT

public:
    explicit ThermostatWidget(Thermostat* thermostat,QWidget *parent = nullptr);
    ~ThermostatWidget();
    void updateUI() override;

private:
    Ui::ThermostatWidget *ui;
    Thermostat* m_thermostat() {return qobject_cast<Thermostat*>(m_device);}
};

#endif // THERMOSTATWIDGET_H
