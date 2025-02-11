#include "hvacwidget.h"
#include "ui_hvacwidget.h"

HVACWidget::HVACWidget(HVAC* unitHVAC, QWidget *parent)
    : DeviceWidget(unitHVAC,parent), ui(new Ui::HVACWidget)
{
    ui->setupUi(this);
    ui->deviceNameLabel->setText(unitHVAC->getName());
    ui->deviceIpLabel->setText("IP: " + unitHVAC->getDeviceIP().toString());
    connect(unitHVAC->getThermostat(),&::Thermostat::temperatureReadingChanged,this,&HVACWidget::onTemperatureChange);
    connect(this,&HVACWidget::sendTemperature,unitHVAC->getThermostat(),&Thermostat::setTemperatureSetting);
    listHVACdevices();
    updateUI();
}

HVACWidget::~HVACWidget()
{
    delete ui;
}

void HVACWidget::updateUI() {
    ui->deviceStatusLabel->setText(QString("Status: %1")
                                       .arg(m_unitHVAC()->getStatus() == DeviceStatus::ON ? "ON" : "OFF"));
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
    HVACdevice->setText(m_unitHVAC()->getThermostat()->getName());
    ui->devicesHVAClistWidget->addItem(HVACdevice);
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
    QListWidgetItem *item = new QListWidgetItem;
    if(ui->newDeviceTypeCoBox->currentIndex() == 0){
        AC newAC;
        newAC.setDeviceName(ui->newDeviceNameLiEd->text());
        qDebug() << "ui->newDeviceNameLiEd->text()";
        newAC.setDeviceIP(address);
        m_unitHVAC()->addAC(&newAC);
    } else {
        Heater newHeater;
        newHeater.setDeviceName(ui->newDeviceNameLiEd->text());
        newHeater.setDeviceIP(address);
        m_unitHVAC()->addHeater(&newHeater);
    }
    qDebug() << "Dodajemy item";
    item->setText(ui->newDeviceNameLiEd->text());
    qDebug() << ui->newDeviceNameLiEd->text();
    ui->devicesHVAClistWidget->addItem(item);
    ui->devicesHVAClistWidget->update();
}

Device* HVACWidget::searchDevice(QString deviceName){
    Device *selectedDevice = nullptr;
    // Znalezienie urządzenia na podstawie nazwy
    if(deviceName == m_unitHVAC()->getThermostat()->getName()){
        selectedDevice =m_unitHVAC()->getThermostat();
    }

    for (AC* device : m_unitHVAC()->getDevicesAC()) {
        qDebug() << device->getName();
        if (device->getName() == deviceName) {
            selectedDevice = device;
            qDebug() << selectedDevice->getName();
            break;
        }
    }
    for (Heater* device : m_unitHVAC()->getDevicesHeater()) {
        if (device->getName() == deviceName) {
            selectedDevice = device;
            qDebug() << selectedDevice->getName();
            break;
        }
    }
    return selectedDevice;
}

void HVACWidget::on_devicesHVAClistWidget_itemClicked(QListWidgetItem *item)
{
    Device *device = searchDevice(item->text());
    ui->deviceNameFromListLabel->setText(device->getName());
        qDebug() << "Dotarło";
    ui->deviceIpFromListLabel->setText(device->getDeviceIP().toString());
    ui->deviceStatusFromListLabel->setText(device->getStatus() == DeviceStatus::ON ? "ON" : "OFF");
}

