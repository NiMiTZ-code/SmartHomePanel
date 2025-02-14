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
    ui->newDeviceNameLiEd->setPlaceholderText("Kitchen device");

    QString ipRange = R"((?:[0-1]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5]))";
    QRegularExpression ipRegex ("^" + ipRange + "(\\." + ipRange + ")" + "(\\." + ipRange + ")" + "(\\." + ipRange + ")$");
    QRegularExpressionValidator *ipValidator = new QRegularExpressionValidator(ipRegex,this);
    ui->newDeviceIpLiEd->setValidator(ipValidator);
    ui->newDeviceIpLiEd->setPlaceholderText("192.168.1.2");
    ui->addHVACdeviceButton->hide();
    emit widgetCreation();
}

HVACWidget::~HVACWidget()
{
    delete ui;
}

void HVACWidget::updateUI() {
    ui->deviceStatusLabel->setText(QString("Status: %1")
                                       .arg(m_unitHVAC()->getStatus() == DeviceStatus::ON ? "ON" : "OFF"));
    ui->temperatureLabel->setText(QString::number(m_unitHVAC()->getThermostat()->getTemperatureReading())+ "°C");
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
        QListWidgetItem *HVACdevice = new QListWidgetItem;
        HVACdevice->setText(device->getName());
        ui->devicesHVAClistWidget->addItem(HVACdevice);
    }
    for(auto device: m_unitHVAC()->getDevicesHeater()){
        QListWidgetItem *HVACdevice = new QListWidgetItem;
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
        AC* newAC = new AC;
        newAC->setDeviceName(ui->newDeviceNameLiEd->text());
        newAC->setDeviceIP(address);
        m_unitHVAC()->addAC(newAC);
    } else {
        Heater* newHeater = new Heater;
        newHeater->setDeviceName(ui->newDeviceNameLiEd->text());
        newHeater->setDeviceIP(address);
        m_unitHVAC()->addHeater(newHeater);
    }
    item->setText(ui->newDeviceNameLiEd->text());
    ui->devicesHVAClistWidget->addItem(item);
    ui->devicesHVAClistWidget->update();
    ui->newDeviceNameLiEd->clear();
    ui->newDeviceIpLiEd->clear();
    ui->addHVACdeviceButton->hide();
    hvacDeviceNameOK = false;
    hvacDeviceIpOK = false;
}

Device* HVACWidget::searchDevice(QString deviceName){
    Device *selectedDevice = nullptr;
    // Znalezienie urządzenia na podstawie nazwy
    if(deviceName == m_unitHVAC()->getThermostat()->getName()){
        selectedDevice =m_unitHVAC()->getThermostat();
    }
    else{
        for (AC* device : m_unitHVAC()->getDevicesAC()) {
            if (device->getName() == deviceName) {
                selectedDevice = device;
                break;
            }
        }
        for (Heater* device : m_unitHVAC()->getDevicesHeater()) {
            if (device->getName() == deviceName) {
                selectedDevice = device;
                break;
            }
        }
    }
    return selectedDevice;
}

void HVACWidget::on_devicesHVAClistWidget_itemClicked(QListWidgetItem *item)
{
    emit widgetCreation();
    Device *device = searchDevice(item->text());
    if(device != nullptr){
        ui->deviceNameFromListLabel->setText(device->getName());
        ui->deviceIpFromListLabel->setText(device->getDeviceIP().toString());
        ui->deviceStatusFromListLabel->setText(device->getStatus() == DeviceStatus::ON ? "ON" : "OFF");
    }

}

void HVACWidget::newDeviceNameAndIpOK(){

    Device* device = nullptr;
    device = searchDevice(ui->newDeviceNameLiEd->text());
    QHostAddress address;
    address.setAddress(ui->newDeviceIpLiEd->text());
    if(ui->newDeviceIpLiEd->hasAcceptableInput()){
        emit searchDevicesNameInNetworkHandler(ui->newDeviceNameLiEd->text());
        emit searchDevicesIpInNetworkHandler(&address);
        qDebug() <<hvacDeviceIpOK;
        if(!ui->newDeviceNameLiEd->text().isEmpty() && device == nullptr && ui->newDeviceIpLiEd->hasAcceptableInput() && checkIfIpNotInUse(address) && hvacDeviceNameOK && hvacDeviceIpOK){
            ui->addHVACdeviceButton->show();
        } else{
            ui->addHVACdeviceButton->hide();
        }
    }
}

void HVACWidget::on_newDeviceNameLiEd_textEdited(const QString &arg1)
{
    newDeviceNameAndIpOK();
}


void HVACWidget::on_newDeviceIpLiEd_textEdited(const QString &arg1)
{

    hvacDeviceIpOK = false; //tu
    newDeviceNameAndIpOK();
}

bool HVACWidget::checkIfIpNotInUse(QHostAddress address){
    if(address == m_unitHVAC()->getThermostat()->getDeviceIP()) {
        return false;
    }
        for (AC* device : m_unitHVAC()->getDevicesAC()) {
            if (device->getDeviceIP() == address) {
                return false;
            }
        }
        for (Heater* device : m_unitHVAC()->getDevicesHeater()) {
            if (device->getDeviceIP() == address) {
                return false;
            }
        }
    return true;
}

void HVACWidget::on_hvacDeviceNameOK(){
    hvacDeviceNameOK = true;
}

void HVACWidget::on_hvacDeviceIpOK(){
    hvacDeviceIpOK = true;
}

void HVACWidget::on_checkIfIpNotInHVACDevices(QHostAddress *ip){
    bool notInUse =checkIfIpNotInUse(*ip);
    qDebug() << " Ip Not in use";
    qDebug() << notInUse;
    if(notInUse){
        emit ipNotInHVACDevices();
    }
}
