#include "hvacwidget.h"
#include "ui_hvacwidget.h"

HVACWidget::HVACWidget(HVAC* unitHVAC, QWidget *parent)
    : DeviceWidget(unitHVAC,parent), ui(new Ui::HVACWidget)
{
    ui->setupUi(this);
    ui->deviceNameLabel->setText(unitHVAC->getThermostat()->getName());
    ui->deviceIpLabel->setText("IP: " + unitHVAC->getThermostat()->getDeviceIP().toString());
    connect(unitHVAC->getThermostat(),&::Thermostat::temperatureReadingChanged,this,&HVACWidget::onTemperatureChange);
    connect(this,&HVACWidget::sendTemperature,unitHVAC->getThermostat(),&Thermostat::setTemperatureSetting);
    listHVACdevices();
}

HVACWidget::~HVACWidget()
{
    delete ui;
}

void HVACWidget::updateUI() {
    ui->deviceStatusLabel->setText(QString("Status: %1")
                                       .arg(m_unitHVAC()->getThermostat()->getStatus() == DeviceStatus::ON ? "ON" : "OFF"));
    ui->temperatureLabel->setText(QString::number(m_unitHVAC()->getThermostat()->getTemperatureReading()));
}
void HVACWidget::onTemperatureChange(){
    updateUI();
}
void HVACWidget::on_setTemperatureButton_clicked()
{
    emit sendTemperature(ui->setTemperatureBox->value());
}

void HVACWidget::listHVACdevices(){
    QListWidgetItem *HVACdevice = new QListWidgetItem;
    for(auto device: m_unitHVAC()->getDevicesAC()){
        HVACdevice->setText(device->getName());
        ui->devicesHVAClistWidget->addItem(HVACdevice);
    }
    for(auto device: m_unitHVAC()->getDevicesHeater()){
        HVACdevice->setText(device->getName());
        ui->devicesHVAClistWidget->addItem(HVACdevice);
    }
}

void HVACWidget::on_addHVACdeviceButton_clicked()
{
    QHostAddress address;
    address.setAddress(ui->newDeviceIpLiEd->text());
    QListWidgetItem item;
    if(ui->newDeviceTypeCoBox->currentText() == "AC"){
        AC newAC;
        newAC.setDeviceName(ui->newDeviceNameLiEd->text());
        newAC.setDeviceIP(address);
        m_unitHVAC()->addAC(&newAC);
    } else {
        Heater newHeater;
        newHeater.setDeviceName(ui->newDeviceNameLiEd->text());
        newHeater.setDeviceIP(address);
        m_unitHVAC()->addHeater(&newHeater);
    }
    item.setText(ui->newDeviceNameLiEd->text());
    ui->devicesHVAClistWidget->addItem(&item);
    ui->devicesHVAClistWidget->update();
}

