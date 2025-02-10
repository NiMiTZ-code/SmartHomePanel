#include "thermostatwidget.h"
#include "ui_thermostatwidget.h"

ThermostatWidget::ThermostatWidget(Thermostat* thermostat, QWidget *parent)
    : DeviceWidget(thermostat,parent), ui(new Ui::ThermostatWidget)
{
    ui->setupUi(this);
    ui->deviceNameLabel->setText(thermostat->getName());
    ui->deviceIpLabel->setText("IP: " + thermostat->getDeviceIP().toString());
}

ThermostatWidget::~ThermostatWidget()
{
    delete ui;
}

void ThermostatWidget::updateUI() {
    ui->deviceStatusLabel->setText(QString("Status: %1")
                                       .arg(m_thermostat()->getStatus() == DeviceStatus::ON ? "ON" : "OFF"));
    ui->toggleButton->setText(m_thermostat()->getStatus() == DeviceStatus::ON ? "Turn OFF" : "Turn ON");
}

void ThermostatWidget::on_toggleButton_clicked()
{
    //add toggle on off for thermostat?
}

