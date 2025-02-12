#include "newdevicewindow.h"
#include "ui_newdevicewindow.h"

newdevicewindow::newdevicewindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::newdevicewindow)
{
    ui->setupUi(this);
    QString ipRange = R"((?:[0-1]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5]))";
    QRegularExpression ipRegex ("^" + ipRange + "(\\." + ipRange + ")" + "(\\." + ipRange + ")" + "(\\." + ipRange + ")$");
    QRegularExpressionValidator *ipValidator = new QRegularExpressionValidator(ipRegex,this);
    ui->deviceNameLnEdit->setPlaceholderText("New device");
    ui->thermostatNameliEd->setPlaceholderText("New Thermostat");
    ui->deviceIPLnEdit->setPlaceholderText("192.168.1.2");
    ui->thermostatIpLiEd->setPlaceholderText("192.168.1.4");
    ui->deviceIPLnEdit->setValidator(ipValidator);
    ui->thermostatIpLiEd->setValidator(ipValidator);
    ui->buttonBox->hide();
}

newdevicewindow::~newdevicewindow()
{
    delete ui;
}

QString newdevicewindow::getDeviceName(){
    return ui->deviceNameLnEdit->text();
}

QString newdevicewindow::getDeviceIP(){
    return ui->deviceIPLnEdit->text();
}
int newdevicewindow::getDeviceType(){
    return ui->deviceTypecBox->currentIndex();
}

void newdevicewindow::on_deviceTypecBox_activated(int index)
{
    if(index == 0){
        ui->thermostatIpLabel->show();
        ui->thermostatNameLabel->show();
        ui->thermostatNameliEd->show();
        ui->thermostatIpLiEd->show();
    } else {
        ui->thermostatNameLabel->hide();
        ui->thermostatIpLabel->hide();
        ui->thermostatNameliEd->hide();
        ui->thermostatIpLiEd->hide();
    }
}

QString newdevicewindow::getThermostatName(){
    return ui->thermostatNameliEd->text();
}

QString newdevicewindow::getThermostatIP(){
    return ui->thermostatIpLiEd->text();
}

void newdevicewindow::on_deviceNameLnEdit_textEdited(const QString &arg1)
{
        emit newDeviceNameCheck(arg1);
}


void newdevicewindow::on_deviceIPLnEdit_textEdited(const QString &arg1)
{
    QHostAddress *address = new QHostAddress;
    address->setAddress(arg1);
    emit newDeviceIpcheck(address);
}


void newdevicewindow::on_thermostatNameliEd_textEdited(const QString &arg1)
{

}


void newdevicewindow::on_thermostatIpLiEd_textEdited(const QString &arg1)
{

}

void newdevicewindow::on_newDeviceNameOK(){
    newDeviceNameOK = true;
}

void newdevicewindow::on_newDeviceIpOK(){
    newDeviceIpOK = true;
}

void newdevicewindow::checkIfInputsOK(){
    qDebug() <<&"IP OK: " [ newDeviceIpOK];
    qDebug() << &"Name OK:" [ newDeviceNameOK];
    if(newDeviceNameOK && newDeviceIpOK){
        ui->buttonBox->show();
    }
}
